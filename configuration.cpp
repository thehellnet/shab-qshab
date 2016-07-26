#include "configuration.hpp"

Configuration::Configuration(QObject *parent) : QObject(parent)
{

}

bool Configuration::getHabRunning() const
{
    return habRunning;
}

void Configuration::setHabRunning(bool value)
{
    habRunning = value;
}

bool Configuration::getLocalGpsRunning() const
{
    return localGpsRunning;
}

void Configuration::setLocalGpsRunning(bool value)
{
    localGpsRunning = value;
}
