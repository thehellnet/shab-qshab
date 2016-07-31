#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWebEngineView>
#include <QStatusBar>

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
        StatusBarWidgets* statusBarWidgets;
        Configuration* config;
        ConfigWindow* configWindow;

        QStatusBar* statusBar;
        QWebEngineView* webView;

        void initWebView();
        void initStatusBar();

    private slots:
        void applicationExit();
        void showConfigWindow();
        void configurationChanged();
};

#endif // MAINWINDOW_HPP
