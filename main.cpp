#include <QApplication>

#include "mainwindow.hpp"
#include "configuration.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationDomain("thehellnet.org");
    QCoreApplication::setOrganizationName("The HellNet.org ");
    QCoreApplication::setApplicationName("qShab");
    QCoreApplication::setApplicationVersion("0.1.0");

    QApplication application(argc, argv);

    Configuration config;

    MainWindow mainWindow;
    mainWindow.setConfig(&config);
    mainWindow.show();

    return application.exec();
}
