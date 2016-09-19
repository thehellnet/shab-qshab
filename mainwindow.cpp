#include <QWebEngineSettings>
#include <QFile>
#include <QUrl>
#include <QPlainTextEdit>
#include <QTextCursor>
#include <QTableWidgetItem>
#include <QPixmap>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "protocol/client.hpp"
#include "protocol/hab.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    config = Configuration::getInstance();

    configWindow = new ConfigWindow(this);
    dataHandler = new DataHandler(this);
    statusBarWidgets = new StatusBarWidgets(this);
    dataLogger = new DataLogger(this);
    aboutDialog = new AboutDialog(this);

    clientsTable = ui->clientsTable;
    statusBar = ui->statusBar;
    webView = ui->webView;

    positionInfoHabLatitudeValue = ui->positionInfoHabLatitudeValue;
    positionInfoHabLongitudeValue = ui->positionInfoHabLongitudeValue;
    positionInfoHabAltitudeValue = ui->positionInfoHabAltitudeValue;
    positionInfoLocalGpsLatitudeValue = ui->positionInfoLocalGpsLatitudeValue;
    positionInfoLocalGpsLongitudeValue = ui->positionInfoLocalGpsLongitudeValue;
    positionInfoLocalGpsAltitudeValue = ui->positionInfoLocalGpsAltitudeValue;

    ratioSocketProgressBar = ui->ratioSocketProgressBar;
    ratioRadioProgressBar = ui->ratioRadioProgressBar;

    clearHabPosition();
    clearLocalGpsPosition();
    clearHabFixStatus();
    clearHabTelemetry();

    initClientsTable();

    connect(dataHandler, SIGNAL(newLine(Line)), this, SLOT(newLine(Line)));
    connect(dataHandler, SIGNAL(newLine(QString)), this, SLOT(appendLogLine(QString)));
    connect(dataHandler, SIGNAL(newSocketState(QAbstractSocket::SocketState)), this, SLOT(handleServerSyncSocketEvent(QAbstractSocket::SocketState)));

    connect(dataHandler, SIGNAL(habPositionUpdated(Hab*)), this, SLOT(updateHabPosition(Hab*)));
    connect(dataHandler, SIGNAL(updateLocalClient(Client*)), this, SLOT(updateLocalGpsPosition(Client*)));
    connect(dataHandler, SIGNAL(updateClientsList()), this, SLOT(updateClientsTable()));
    connect(dataHandler, SIGNAL(removeAllRemoteClients()), this, SLOT(removeAllRemoteClients()));

    connect(dataHandler, SIGNAL(habPositionUpdated(Hab*)), this, SLOT(mapHabUpdate(Hab*)));
    connect(dataHandler, SIGNAL(updateLocalClient(Client*)), this, SLOT(mapLocalClientUpdate(Client*)));
    connect(dataHandler, SIGNAL(addRemoteClient(Client*)), this, SLOT(mapRemoteClientAdd(Client*)));
    connect(dataHandler, SIGNAL(updateRemoteClient(Client*)), this, SLOT(mapRemoteClientUpdate(Client*)));
    connect(dataHandler, SIGNAL(removeRemoteClient(Client*)), this, SLOT(mapRemoteClientRemove(Client*)));

    connect(dataHandler, SIGNAL(habImageSlice(Hab*)), this, SLOT(handleImageSlice(Hab*)));
    connect(dataHandler, SIGNAL(newImage(QByteArray)), this, SLOT(handleNewImage(QByteArray)));
    connect(dataHandler, SIGNAL(habPositionUpdated(Hab*)), this, SLOT(updateHabFixStatus(Hab*)));
    connect(dataHandler, SIGNAL(habTelemetryUpdated(Hab*)), this, SLOT(updateHabTelemetry(Hab*)));

    connect(dataHandler, SIGNAL(updateRatio(int, int)), this, SLOT(updateRatioProgressBars(int, int)));
    connect(dataHandler, SIGNAL(updateErrors(int, int)), this, SLOT(updateErrorsProgressBar(int, int)));

    configWindow->setModal(true);
    connect(configWindow, SIGNAL(configurationChanged()), this, SLOT(configurationChanged()));
    connect(configWindow, SIGNAL(configurationChanged()), dataHandler, SLOT(reloadLocalClient()));

    statusBarWidgets->updateFromConfig();

    connect(dataHandler, SIGNAL(newLine(QString)), dataLogger, SLOT(saveLine(QString)));
    connect(dataLogger, SIGNAL(imageSaved(QString)), this, SLOT(imageSaved(QString)));

    initStatusBar();

    initWebView();

    connect(ui->actionFileExit, SIGNAL(triggered(bool)), this, SLOT(applicationExit()));
    connect(ui->actionFileConfig, SIGNAL(triggered(bool)), this, SLOT(showConfigWindow()));

    connect(ui->actionStatusHAB, SIGNAL(triggered(bool)), this, SLOT(toogleHab()));
    connect(ui->actionStatusLocalGPS, SIGNAL(triggered(bool)), this, SLOT(toogleLocalGps()));
    connect(ui->actionStatusServerSync, SIGNAL(triggered(bool)), this, SLOT(toogleServerSync()));

    connect(ui->actionStatusMapAuto, SIGNAL(triggered(bool)), this, SLOT(toogleMapAutoBoundsAndZoom()));

    connect(ui->actionHelpAbout, SIGNAL(triggered(bool)), this, SLOT(showAboutDialog()));

    updateActionEnableStatus();
}

MainWindow::~MainWindow()
{
    delete dataLogger;
    delete statusBarWidgets;
    delete configWindow;
    delete dataHandler;
    delete aboutDialog;

    delete ui;
}

void MainWindow::initWebView()
{
#ifdef QT_DEBUG
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "9000");
#endif

    QWebEngineSettings* settings = webView->settings();
    settings->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, false);
    settings->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    settings->setAttribute(QWebEngineSettings::WebGLEnabled, true);
    settings->setAttribute(QWebEngineSettings::XSSAuditingEnabled, false);

    webView->load(QUrl("qrc:/maps.html"));
}

void MainWindow::initStatusBar()
{
    statusBar->addPermanentWidget(statusBarWidgets->serverSync);
    statusBar->addPermanentWidget(statusBarWidgets->localGpsSerial);
    statusBar->addPermanentWidget(statusBarWidgets->habSerial);
    statusBar->addPermanentWidget(statusBarWidgets->time);
}

void MainWindow::initClientsTable()
{
    clientsTable->setColumnCount(2);

    QStringList labels;
    labels.append("ID");
    labels.append("Name");
    clientsTable->setHorizontalHeaderLabels(labels);
}

void MainWindow::applicationExit()
{
    close();
}

void MainWindow::showConfigWindow()
{
    configWindow->init();
    configWindow->exec();
}

void MainWindow::showStatusBarMessage(QString message, int timeout)
{
    ui->statusBar->showMessage(message, timeout);
}

void MainWindow::updateActionEnableStatus()
{
    ui->actionStatusLocalGPS->setEnabled(config->getLocalGpsSerialEnable());
    ui->actionStatusServerSync->setEnabled(config->getServerSyncEnable());
}

void MainWindow::configurationChanged()
{
    showStatusBarMessage("Configuration saved");

    updateActionEnableStatus();
    statusBarWidgets->updateFromConfig();
}

void MainWindow::toogleHab()
{
    bool status = !config->getHabRunning();
    ui->actionStatusHAB->setChecked(status);

    if(status) {
        dataHandler->startHab();
    } else {
        dataHandler->stopHab();
        clearHabPosition();
        mapHabRemove();
        clearHabFixStatus();
        clearHabTelemetry();
    }

    config->setHabRunning(status);

    if(status)
        showStatusBarMessage("Hab Serial port start");
    else
        showStatusBarMessage("Hab Serial port stop");

    statusBarWidgets->updateFromConfig();
}

void MainWindow::updateHabPosition(Hab* hab)
{
    positionInfoHabLatitudeValue->setText(QString::number(hab->getLatitude()));
    positionInfoHabLongitudeValue->setText(QString::number(hab->getLongitude()));
    positionInfoHabAltitudeValue->setText(QString::number(hab->getAltitude()));
}

void MainWindow::clearHabPosition()
{
    positionInfoHabLatitudeValue->setText("");
    positionInfoHabLongitudeValue->setText("");
    positionInfoHabAltitudeValue->setText("");
}

void MainWindow::updateLocalGpsPosition(Client* client)
{
    positionInfoLocalGpsLatitudeValue->setText(QString::number(client->getPosition().latitude()));
    positionInfoLocalGpsLongitudeValue->setText(QString::number(client->getPosition().longitude()));
    positionInfoLocalGpsAltitudeValue->setText(QString::number(client->getPosition().altitude()));
}

void MainWindow::clearLocalGpsPosition()
{
    positionInfoLocalGpsLatitudeValue->setText("");
    positionInfoLocalGpsLongitudeValue->setText("");
    positionInfoLocalGpsAltitudeValue->setText("");
}

void MainWindow::toogleLocalGps()
{
    bool status = !config->getLocalGpsRunning();
    ui->actionStatusLocalGPS->setChecked(status);

    if(status) {
        dataHandler->startLocalGps();
    } else {
        dataHandler->stopLocalGps();
        clearLocalGpsPosition();
        mapLocalClientRemove();
    }

    config->setLocalGpsRunning(status);

    if(status)
        showStatusBarMessage("Local GPS start");
    else
        showStatusBarMessage("Local GPS stop");

    if(!status)
        mapExecJS("removeLocal();");

    statusBarWidgets->updateFromConfig();
}

void MainWindow::toogleServerSync()
{
    bool status = !config->getServerSyncRunning();
    ui->actionStatusServerSync->setChecked(status);

    if(status)
        dataHandler->startServerSync();
    else
        dataHandler->stopServerSync();

    config->setServerSyncRunning(status);

    if(status)
        showStatusBarMessage("Server Sync start");
    else
        showStatusBarMessage("Server Sync stop");

    statusBarWidgets->updateFromConfig();
}

void MainWindow::toogleMapAutoBoundsAndZoom()
{
    bool status = ui->actionStatusMapAuto->isChecked();
    ui->actionStatusMapAuto->setChecked(status);

    if(status)
        mapExecJS("setAutoBounds(true);");
    else
        mapExecJS("setAutoBounds(false);");
}

void MainWindow::handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState)
{
    switch(socketState) {
        case QAbstractSocket::HostLookupState:
            showStatusBarMessage("Host lookup...");
            break;
        case QAbstractSocket::ConnectingState:
            showStatusBarMessage("Connecting...");
            break;
        case QAbstractSocket::ConnectedState:
            showStatusBarMessage("Socket connected");
            break;
        case QAbstractSocket::ClosingState:
            showStatusBarMessage("Socket closing...");
            break;
        default:
            showStatusBarMessage("Socket not connected");
    }
}

void MainWindow::appendLogLine(QString line)
{
    QPlainTextEdit* logText = ui->logText;
    logText->appendPlainText(QString("%1 - %2")
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz"))
                    .arg(line.simplified()));

    QTextCursor cursor = logText->textCursor();
    while(logText->blockCount() > 50) {
        cursor.movePosition(QTextCursor::Start);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        cursor.deleteChar();
    }

    cursor.movePosition(QTextCursor::End);
}

void MainWindow::imageSaved(QString imageName)
{
    QString message = "Image saved: " + imageName;
    showStatusBarMessage(message);
}

void MainWindow::updateClientsTable()
{
    QList<Client*>* clients = dataHandler->getClients();

    clientsTable->clearContents();
    clientsTable->setRowCount(clients->count());

    for(int i = 0; i < clients->count(); i++) {
        QTableWidgetItem* idItem = new QTableWidgetItem();
        idItem->setText(clients->at(i)->getId());
        QTableWidgetItem* nameItem = new QTableWidgetItem();
        nameItem->setText(clients->at(i)->getName());
        clientsTable->setItem(i, 0, idItem);
        clientsTable->setItem(i, 1, nameItem);
    }

    clientsTable->resizeColumnsToContents();
}

void MainWindow::removeAllRemoteClients()
{
    clientsTable->clearContents();
    clientsTable->setRowCount(0);
    clientsTable->resizeColumnsToContents();

    mapRemoteClientClear();
}

void MainWindow::mapHabUpdate(Hab* hab)
{
    mapExecJS(QString("updateHab(%1, %2);").arg(hab->getLatitude()).arg(hab->getLongitude()));
}

void MainWindow::mapHabRemove()
{
    mapExecJS("removeHab();");
}

void MainWindow::mapExecJS(QString jsCode)
{
    webView->page()->runJavaScript(jsCode);
}

void MainWindow::mapLocalClientUpdate(Client* client)
{
    mapExecJS(QString("updateLocal(%1, %2);")
              .arg(client->getPosition().latitude())
              .arg(client->getPosition().longitude()));
}

void MainWindow::mapLocalClientRemove()
{
    mapExecJS("removeLocal();");
}

void MainWindow::mapRemoteClientClear()
{
    mapExecJS("removeAllRemoteClients();");
}

void MainWindow::mapRemoteClientAdd(Client* client)
{
    mapExecJS(QString("addRemoteClient(\"%1\", \"%2\");").arg(client->getId()).arg(client->getName()));
}

void MainWindow::mapRemoteClientUpdate(Client* client)
{
    mapExecJS(QString("updateRemoteClient(\"%1\", %2, %3);")
              .arg(client->getId())
              .arg(client->getPosition().latitude())
              .arg(client->getPosition().longitude()));
}

void MainWindow::mapRemoteClientRemove(Client* client)
{
    mapExecJS(QString("removeRemoteClient(\"%1\");").arg(client->getId()));
}

void MainWindow::updateHabFixStatus(Hab* hab)
{
    switch (hab->getFixStatus()) {
        case 1:
            ui->infoHabFixStatusValue->setText("GPS fix (SPS)");
            break;
        case 2:
            ui->infoHabFixStatusValue->setText("DGPS fix");
            break;
        case 3:
            ui->infoHabFixStatusValue->setText("PPS fix");
            break;
        case 4:
            ui->infoHabFixStatusValue->setText("Real Time Kinematic");
            break;
        case 5:
            ui->infoHabFixStatusValue->setText("Float RTK");
            break;
        case 6:
            ui->infoHabFixStatusValue->setText("Estimated (dead reckoning)");
            break;
        case 7:
            ui->infoHabFixStatusValue->setText("Manual input");
            break;
        case 8:
            ui->infoHabFixStatusValue->setText("Simulation mode");
            break;
        default:
            ui->infoHabFixStatusValue->setText("invalid");
    }
}

void MainWindow::clearHabFixStatus()
{
    ui->infoHabFixStatusValue->setText("");
}

void MainWindow::handleImageSlice(Hab* hab)
{
    ui->infoImageProgressBar->setMaximum(hab->getSliceTot());
    ui->infoImageProgressBar->setValue(hab->getSliceNum());
}

void MainWindow::handleNewImage(QByteArray imageData)
{
    QPixmap pixmap;
    if(pixmap.loadFromData(imageData, "JPG"))
        ui->imageLabel->setPixmap(pixmap);
}

void MainWindow::updateHabTelemetry(Hab* hab)
{
    ui->infoTelemetryIntTempValue->setText(QString("%1 °C").arg(hab->getIntTemp(), 0, 'f', 1));
    ui->infoTelemetryExtTempValue->setText(QString("%1 °C").arg(hab->getExtTemp(), 0, 'f', 1));
    ui->infoTelemetryExtAltValue->setText(QString("%1 m").arg(hab->getExtAlt(), 0, 'f', 1));
}

void MainWindow::clearHabTelemetry()
{
    ui->infoTelemetryIntTempValue->setText("");
    ui->infoTelemetryExtTempValue->setText("");
    ui->infoTelemetryExtAltValue->setText("");
}

void MainWindow::showAboutDialog()
{
    aboutDialog->show();
}

void MainWindow::updateRatioProgressBars(int radioLines, int socketLines)
{
    int max = radioLines + socketLines;
    ratioRadioProgressBar->setMaximum(max);
    ratioRadioProgressBar->setValue(radioLines);
    ratioSocketProgressBar->setMaximum(max);
    ratioSocketProgressBar->setValue(socketLines);
}

void MainWindow::updateErrorsProgressBar(int errors, int lines)
{
    ui->infoErrorProgressBar->setMaximum(lines);
    ui->infoErrorProgressBar->setValue(errors);
}
