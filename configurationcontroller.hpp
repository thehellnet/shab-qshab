#ifndef CONFIGURATIONCONTROLLER_HPP
#define CONFIGURATIONCONTROLLER_HPP

#include <QObject>

class ConfigurationController
{
    public:
        ConfigurationController();
        static void loadConfig(Configuration* config);
        static void saveConfig(Configuration* config);
};

#endif // CONFIGURATIONCONTROLLER_HPP
