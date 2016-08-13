#include "data/gpshandler.hpp"

GPSHandler::GPSHandler(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();

    source = new QNmeaPositionInfoSource(QNmeaPositionInfoSource::RealTimeMode, this);
    serial = new QSerialPort(this);

    connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positionUpdated(QGeoPositionInfo)));
}

GPSHandler::~GPSHandler()
{
    delete serial;
    delete source;
}

void GPSHandler::start()
{
    serial->setPortName(config->getLocalGpsSerialPort());
    serial->setBaudRate(config->getLocalGpsSerialSpeed());
    serial->setFlowControl(config->getLocalGpsSerialFlowControl());
    serial->setParity(config->getLocalGpsSerialParity());
    serial->setDataBits(config->getLocalGpsSerialDataBits());
    serial->setStopBits(config->getLocalGpsSerialStopBits());

    if(!serial->open(QIODevice::ReadWrite))
        return;

    source->setDevice(serial);
    source->startUpdates();
}

void GPSHandler::stop()
{
    source->stopUpdates();

    serial->close();
}

void GPSHandler::positionUpdated(QGeoPositionInfo positionInfo)
{
    emit newPosition(positionInfo.coordinate());
}
