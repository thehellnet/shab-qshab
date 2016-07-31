#include <QSettings>
#include <QVariant>
#include <QString>
#include <QtSerialPort/QtSerialPort>

#include "configurationcontroller.hpp"

ConfigurationController::ConfigurationController()
{

}

void ConfigurationController::loadConfig(Configuration* config)
{
    QSettings settings;

    settings.beginGroup("hab");
    config->setHabSerialPort(settings.value("serialPort", "444").toString());
    config->setHabSerialSpeed(settings.value("serialSpeed", QSerialPort::Baud9600).value<QSerialPort::BaudRate>());
    settings.endGroup();

    settings.beginGroup("localGps");
    config->setLocalGpsSerialPort(settings.value("serialPort", "").toString());
    config->setLocalGpsSerialSpeed(settings.value("serialSpeed", QSerialPort::Baud9600).value<QSerialPort::BaudRate>());
    config->setLocalGpsSerialFlowControl(settings.value("serialFlowControl", QSerialPort::NoFlowControl).value<QSerialPort::FlowControl>());
    config->setLocalGpsSerialParity(settings.value("serialParity", QSerialPort::NoParity).value<QSerialPort::Parity>());
    config->setLocalGpsSerialDataBits(settings.value("serialDataBits", QSerialPort::Data8).value<QSerialPort::DataBits>());
    config->setLocalGpsSerialStopBits(settings.value("serialStopBits", QSerialPort::OneStop).value<QSerialPort::StopBits>());
    settings.endGroup();

    settings.beginGroup("serverSync");
    config->setServerSyncEnable(settings.value("enable", false).toBool());
    config->setServerSyncAddress(settings.value("address", "").toString());
    config->setServerSyncPort(settings.value("port", 12345).toUInt());
    settings.endGroup();

    settings.beginGroup("log");
    config->setLogRawEnable(settings.value("rawEnable", false).toBool());
    config->setLogRawPath(settings.value("rawPath", "").toString());
    config->setLogImagesEnable(settings.value("imagesEnable", false).toUInt());
    config->setLogImagesPath(settings.value("imagesPath", "").toString());
    settings.endGroup();
}

void ConfigurationController::saveConfig(Configuration* config)
{
    QSettings settings;

    settings.beginGroup("hab");
    settings.setValue("serialPort", config->getHabSerialPort());
    settings.setValue("serialSpeed", config->getHabSerialSpeed());
    settings.endGroup();

    settings.beginGroup("localGps");
    settings.setValue("serialPort", config->getLocalGpsSerialPort());
    settings.setValue("serialFlowControl", config->getLocalGpsSerialFlowControl());
    settings.setValue("serialSpeed", config->getLocalGpsSerialSpeed());
    settings.setValue("serialParity", config->getLocalGpsSerialParity());
    settings.setValue("serialDataBits", config->getLocalGpsSerialDataBits());
    settings.setValue("serialStopBits", config->getLocalGpsSerialStopBits());
    settings.endGroup();

    settings.beginGroup("serverSync");
    settings.setValue("enable", config->getServerSyncEnable());
    settings.setValue("address", config->getServerSyncAddress());
    settings.setValue("port", config->getServerSyncPort());
    settings.endGroup();

    settings.beginGroup("log");
    settings.setValue("rawEnable", config->getLogRawEnable());
    settings.setValue("rawPath", config->getLogRawPath());
    settings.setValue("imagesEnable", config->getLogImagesEnable());
    settings.setValue("imagesPath", config->getLogImagesPath());
    settings.endGroup();

    settings.sync();
}
