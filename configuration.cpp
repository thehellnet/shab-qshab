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

bool Configuration::getServerSyncRunning() const
{
    return serverSyncRunning;
}

void Configuration::setServerSyncRunning(bool value)
{
    serverSyncRunning = value;
}

QString Configuration::getHabSerialPort() const
{
    return habSerialPort;
}

void Configuration::setHabSerialPort(const QString& value)
{
    habSerialPort = value;
}

QSerialPort::BaudRate Configuration::getHabSerialSpeed() const
{
    return habSerialSpeed;
}

void Configuration::setHabSerialSpeed(const QSerialPort::BaudRate& value)
{
    habSerialSpeed = value;
}

bool Configuration::getLocalGpsSerialEnable() const
{
    return localGpsSerialEnable;
}

void Configuration::setLocalGpsSerialEnable(bool value)
{
    localGpsSerialEnable = value;
}

QString Configuration::getLocalGpsSerialPort() const
{
    return localGpsSerialPort;
}

void Configuration::setLocalGpsSerialPort(const QString& value)
{
    localGpsSerialPort = value;
}

QSerialPort::BaudRate Configuration::getLocalGpsSerialSpeed() const
{
    return localGpsSerialSpeed;
}

void Configuration::setLocalGpsSerialSpeed(const QSerialPort::BaudRate& value)
{
    localGpsSerialSpeed = value;
}

QSerialPort::FlowControl Configuration::getLocalGpsSerialFlowControl() const
{
    return localGpsSerialFlowControl;
}

void Configuration::setLocalGpsSerialFlowControl(const QSerialPort::FlowControl& value)
{
    localGpsSerialFlowControl = value;
}

QSerialPort::Parity Configuration::getLocalGpsSerialParity() const
{
    return localGpsSerialParity;
}

void Configuration::setLocalGpsSerialParity(const QSerialPort::Parity& value)
{
    localGpsSerialParity = value;
}

QSerialPort::DataBits Configuration::getLocalGpsSerialDataBits() const
{
    return localGpsSerialDataBits;
}

void Configuration::setLocalGpsSerialDataBits(const QSerialPort::DataBits& value)
{
    localGpsSerialDataBits = value;
}

QSerialPort::StopBits Configuration::getLocalGpsSerialStopBits() const
{
    return localGpsSerialStopBits;
}

void Configuration::setLocalGpsSerialStopBits(const QSerialPort::StopBits& value)
{
    localGpsSerialStopBits = value;
}

bool Configuration::getServerSyncEnable() const
{
    return serverSyncEnable;
}

void Configuration::setServerSyncEnable(bool value)
{
    serverSyncEnable = value;
}

QString Configuration::getServerSyncAddress() const
{
    return serverSyncAddress;
}

void Configuration::setServerSyncAddress(const QString& value)
{
    serverSyncAddress = value;
}

quint16 Configuration::getServerSyncPort() const
{
    return serverSyncPort;
}

void Configuration::setServerSyncPort(const quint16& value)
{
    serverSyncPort = value;
}

bool Configuration::getLogRawEnable() const
{
    return logRawEnable;
}

void Configuration::setLogRawEnable(bool value)
{
    logRawEnable = value;
}

QString Configuration::getLogRawPath() const
{
    return logRawPath;
}

void Configuration::setLogRawPath(const QString& value)
{
    logRawPath = value;
}

bool Configuration::getLogImagesEnable() const
{
    return logImagesEnable;
}

void Configuration::setLogImagesEnable(bool value)
{
    logImagesEnable = value;
}

QString Configuration::getLogImagesPath() const
{
    return logImagesPath;
}

void Configuration::setLogImagesPath(const QString& value)
{
    logImagesPath = value;
}
