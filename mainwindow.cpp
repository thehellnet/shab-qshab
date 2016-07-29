#include <QWebEngineSettings>
#include <QFile>
#include <QUrl>

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    config = Configuration::getInstance();

    configWindow = new ConfigWindow(this);
    configWindow->setModal(true);
    connect(configWindow, SIGNAL(configurationChanged()), this, SLOT(configurationChanged()));

    connect(ui->actionFileExit, SIGNAL(triggered(bool)), this, SLOT(applicationExit()));
    connect(ui->actionFileConfig, SIGNAL(triggered(bool)), this, SLOT(showConfigWindow()));

    statusBarWidgets = new StatusBarWidgets(this);
    statusBar = ui->statusBar;
    initStatusBar();

    webView = ui->webView;
    initWebView();
}

MainWindow::~MainWindow()
{
    delete statusBarWidgets;
    delete configWindow;
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
    configWindow->exec();
}

void MainWindow::configurationChanged()
{
    ui->statusBar->showMessage("Configuration saved", 2000);
    statusBarWidgets->updateFromConfig();
}
