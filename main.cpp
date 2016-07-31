#include <QApplication>

#include "mainwindow.hpp"
#include "configwindow.hpp"
#include "config/configuration.hpp"
#include "config/configurationcontroller.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationDomain("thehellnet.org");
    QCoreApplication::setOrganizationName("The HellNet.org");
    QCoreApplication::setApplicationName("qShab");
    QCoreApplication::setApplicationVersion("0.0.7");

    QApplication application(argc, argv);

    Configuration* config = Configuration::getInstance();
    ConfigurationController::loadConfig(config);

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}
