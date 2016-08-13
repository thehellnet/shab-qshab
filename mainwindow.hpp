#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWebEngineView>
#include <QStatusBar>
#include <QTableWidget>

#include "data/datahandler.hpp"
#include "config/configuration.hpp"
#include "configwindow.hpp"
#include "statusbarwidgets.hpp"
#include "datalogger.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow* ui;
        Configuration* config;
        DataHandler* dataHandler;
        ConfigWindow* configWindow;
        StatusBarWidgets* statusBarWidgets;
        DataLogger* dataLogger;
        QTableWidget* clientsTable;

        QStatusBar* statusBar;
        QWebEngineView* webView;

        void initWebView();
        void initStatusBar();
        void initClientsTable();
        void showStatusBarMessage(QString message, int timeout = 3000);

    private slots:
        void applicationExit();
        void showConfigWindow();
        void updateActionEnableStatus();
        void configurationChanged();
        void toogleHab();
        void toogleLocalGps();
        void toogleServerSync();
        void newLine(Line line);
        void handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState);
        void appendLogLine(QString line);
        void imageSaved(QString imageName);
        void updateClientsTable();
        void updateClient(Client* client);
        void updateLocalClient(Client* client);
};

#endif // MAINWINDOW_HPP
