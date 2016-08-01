#include <QWebEngineSettings>
#include <QFile>
#include <QUrl>
#include <QTextEdit>
#include <QTextCursor>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    config = Configuration::getInstance();

    dataHandler = new DataHandler(this);
    connect(dataHandler, SIGNAL(newLine(Line)), this, SLOT(newLine(Line)));
    connect(dataHandler, SIGNAL(newSocketState(QAbstractSocket::SocketState)), this, SLOT(handleServerSyncSocketEvent(QAbstractSocket::SocketState)));

    configWindow = new ConfigWindow(this);
    configWindow->setModal(true);
    connect(configWindow, SIGNAL(configurationChanged()), this, SLOT(configurationChanged()));

    statusBarWidgets = new StatusBarWidgets(this);
    statusBarWidgets->updateFromConfig();

    statusBar = ui->statusBar;
    initStatusBar();

    webView = ui->webView;
    initWebView();

    connect(ui->actionFileExit, SIGNAL(triggered(bool)), this, SLOT(applicationExit()));
    connect(ui->actionFileConfig, SIGNAL(triggered(bool)), this, SLOT(showConfigWindow()));

    connect(ui->actionStatusHAB, SIGNAL(triggered(bool)), this, SLOT(toogleHab()));
    connect(ui->actionStatusLocalGPS, SIGNAL(triggered(bool)), this, SLOT(toogleLocalGps()));
    connect(ui->actionStatusServerSync, SIGNAL(triggered(bool)), this, SLOT(toogleServerSync()));

    updateActionEnableStatus();
}

MainWindow::~MainWindow()
{
    delete statusBarWidgets;
    delete configWindow;
    delete dataHandler;
    delete ui;
}

void MainWindow::initWebView()
{
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

    if(status)
        dataHandler->startHab();
    else
        dataHandler->stopHab();

    config->setHabRunning(status);

    if(status)
        showStatusBarMessage("Hab Serial port start");
    else
        showStatusBarMessage("Hab Serial port stop");

    statusBarWidgets->updateFromConfig();
}

void MainWindow::toogleLocalGps()
{
    bool status = !config->getLocalGpsRunning();
    ui->actionStatusLocalGPS->setChecked(status);

    if(status)
        dataHandler->startLocalGps();
    else
        dataHandler->stopLocalGps();

    config->setLocalGpsRunning(status);

    if(status)
        showStatusBarMessage("Local GPS start");
    else
        showStatusBarMessage("Local GPS stop");

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
    QTextEdit* logText = ui->logText;
    logText->append(line + "\n");

    while(logText->document()->lineCount() > 50) {
        QTextCursor cursor = logText->textCursor();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, 0);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.removeSelectedText();
    }

    cursor.movePosition(QTextCursor::End);
}

void MainWindow::newLine(Line line)
{
    appendLogLine(line.getRawLine());
}
