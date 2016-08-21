#include "habhandler.hpp"

HabHandler::HabHandler(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();

    serial = new QSerialPort(this);
    connect(serial, SIGNAL(readyRead()), this, SLOT(readLine()));
}

HabHandler::~HabHandler()
{
    delete serial;
}

bool HabHandler::isRunning() const
{
    return running;
}

void HabHandler::start()
{
    serial->setPortName(config->getHabSerialPort());
    serial->setBaudRate(config->getHabSerialSpeed());
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);

    if(!serial->open(QIODevice::ReadWrite))
        return;

    running = true;
}

void HabHandler::stop()
{
    serial->close();

    running = false;
}

void HabHandler::readLine()
{
    if(!serial->canReadLine())
        return;

    QString line = QString(serial->readLine());
    emit newLine(line);
}
