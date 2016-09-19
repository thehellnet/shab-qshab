#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWebEngineView>
#include <QStatusBar>
#include <QTableWidget>
#include <QProgressBar>

#include "data/datahandler.hpp"
#include "config/configuration.hpp"
#include "configwindow.hpp"
#include "statusbarwidgets.hpp"
#include "datalogger.hpp"
#include "aboutdialog.hpp"

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
        AboutDialog* aboutDialog;

        QStatusBar* statusBar;
        QWebEngineView* webView;
        QLabel* positionInfoHabLatitudeValue;
        QLabel* positionInfoHabLongitudeValue;
        QLabel* positionInfoHabAltitudeValue;
        QLabel* positionInfoLocalGpsLatitudeValue;
        QLabel* positionInfoLocalGpsLongitudeValue;
        QLabel* positionInfoLocalGpsAltitudeValue;

        QProgressBar* ratioSocketProgressBar;
        QProgressBar* ratioRadioProgressBar;

        void initWebView();
        void initStatusBar();
        void initClientsTable();
        void showStatusBarMessage(QString message, int timeout = 3000);

        void mapExecJS(QString jsCode);

        void clearHabPosition();
        void clearLocalGpsPosition();
        void mapRemoteClientClear();

        void clearHabFixStatus();
        void clearHabTelemetry();

    private slots:
        void applicationExit();
        void showConfigWindow();
        void updateActionEnableStatus();
        void configurationChanged();
        void toogleHab();
        void toogleLocalGps();
        void toogleServerSync();
        void toogleMapAutoBoundsAndZoom();
        void handleServerSyncSocketEvent(QAbstractSocket::SocketState socketState);
        void appendLogLine(QString line);
        void imageSaved(QString imageName);
        void updateClientsTable();
        void removeAllRemoteClients();

        void updateHabPosition(Hab* hab);
        void updateLocalGpsPosition(Client* client);

        void mapHabUpdate(Hab* hab);
        void mapHabRemove();
        void mapLocalClientUpdate(Client* client);
        void mapLocalClientRemove();
        void mapRemoteClientAdd(Client* client);
        void mapRemoteClientUpdate(Client* client);
        void mapRemoteClientRemove(Client* client);

        void handleImageSlice(Hab* hab);
        void handleNewImage(QByteArray imageData);
        void updateHabFixStatus(Hab* hab);
        void updateHabTelemetry(Hab* hab);

        void showAboutDialog();

        void updateRatioProgressBars(int radioLines, int socketLines);
        void updateErrorsProgressBar(int errors, int lines);
};

#endif // MAINWINDOW_HPP
