#include <QApplication>

#include "mainwindow.hpp"
#include "configuration.hpp"
#include "configurationcontroller.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationDomain("thehellnet.org");
    QCoreApplication::setOrganizationName("The HellNet.org ");
    QCoreApplication::setApplicationName("qShab");
    QCoreApplication::setApplicationVersion("0.1.0");

    Configuration* config = Configuration::getInstance();
    ConfigurationController::loadConfig(config);

    QApplication application(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
