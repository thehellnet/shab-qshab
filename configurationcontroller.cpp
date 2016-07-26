#include <QSettings>

#include "configurationcontroller.hpp"
#include "configuration.hpp"

ConfigurationController::ConfigurationController()
{

}

void ConfigurationController::loadConfig(Configuration* config)
{
    if(!config->getHabRunning()) {

    }

    if(config->getHabRunning()) {

    }
}

void ConfigurationController::saveConfig(Configuration* config)
{
    QSettings settings;

}
