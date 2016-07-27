#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QWebEngineView>

#include "configuration.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void setConfig(Configuration* value);

    private:
        Ui::MainWindow *ui;
        Configuration* config;
        QWebEngineView* webView;

        void initWebView(QWebEngineView* webView);

    private slots:
        void applicationExit();
        void showConfigWindow();
};

#endif // MAINWINDOW_HPP
