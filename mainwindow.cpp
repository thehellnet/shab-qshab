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

    connect(ui->actionFileExit, SIGNAL(triggered(bool)), this, SLOT(applicationExit()));

    webView = ui->webView;
    initWebView(webView);
    webView->load(QUrl("qrc:/maps.html"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setConfig(Configuration* value)
{
    config = value;
}

void MainWindow::initWebView(QWebEngineView* webView)
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
}

void MainWindow::applicationExit()
{
    close();
}
