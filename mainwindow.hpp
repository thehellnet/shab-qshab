#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWebEngineView>
#include <QStatusBar>

#include "data/datahandler.hpp"
#include "config/configuration.hpp"
#include "configwindow.hpp"
#include "statusbarwidgets.hpp"

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

        QStatusBar* statusBar;
        QWebEngineView* webView;

        void initWebView();
        void initStatusBar();
        void showStatusBarMessage(QString message, int timeout = 3000);

    private slots:
        void applicationExit();
        void showConfigWindow();
        void configurationChanged();
        void toogleHab();
        void toogleLocalGps();
        void toogleServerSync();
        void newLine(Line line);
};

#endif // MAINWINDOW_HPP
