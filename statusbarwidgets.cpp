#include <QDateTime>

#include "statusbarwidgets.hpp"
#include "utility.hpp"

StatusBarWidgets::StatusBarWidgets(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();

    time = new QLabel();
    initLabelStyle(time);
    initTime();

    habSerial = new QLabel();
    initLabelStyle(habSerial);
    initHabSerial();

    localGpsSerial = new QLabel();
    initLabelStyle(localGpsSerial);
    initLocalGpsSerial();

    serverSync = new QLabel();
    initLabelStyle(serverSync);
    initServerSync();

    timeTimer = new QTimer();
    initTimeTimer();

    updateFromConfig();
}

StatusBarWidgets::~StatusBarWidgets()
{
    delete time;
}

void StatusBarWidgets::initLabelStyle(QLabel* label)
{
//    label->setFrameShape(QFrame::StyledPanel);
//    label->setFrameShadow(QFrame::Sunken);
    label->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    label->setMinimumWidth(50);
    label->setStyleSheet("padding-left: 3px; padding-right: 3px;");
}

void StatusBarWidgets::initTime()
{
    time->setText("time");
    time->setMinimumWidth(140);
    time->setMaximumWidth(140);
    time->setStyleSheet("");
}

void StatusBarWidgets::initHabSerial()
{
    habSerial->setText("habSerial");
}

void StatusBarWidgets::initLocalGpsSerial()
{
    localGpsSerial->setText("localGps");
}

void StatusBarWidgets::initServerSync()
{
    serverSync->setText("serverSync");
}

void StatusBarWidgets::initTimeTimer()
{
    timeTimer->setInterval(1000);
    timeTimer->setSingleShot(false);
    timeTimer->setTimerType(Qt::VeryCoarseTimer);
    timeTimer->start();
    connect(timeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    updateTime();
}

void StatusBarWidgets::updateTime()
{
    time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void StatusBarWidgets::updateFromConfig()
{
    QString text;

    text = QString("<strong>HAB:</strong> %1 %2 %3")
           .arg(config->getHabSerialPort())
           .arg(config->getHabSerialSpeed())
           .arg(Utility::serialPortParams(QSerialPort::Data8, QSerialPort::NoParity, QSerialPort::OneStop));
    habSerial->setText(text);
    habSerial->setEnabled(config->getHabRunning());

    text = "<strong>Local GPS:</strong> disabled";
    if(config->getLocalGpsSerialEnable() && config->getLocalGpsSerialPort().length() > 0) {
        QString serialPortParams = Utility::serialPortParams(config->getLocalGpsSerialDataBits(),
                                                     config->getLocalGpsSerialParity(),
                                                     config->getLocalGpsSerialStopBits());
        text = QString("<strong>Local GPS:</strong> %1 %2 %3")
               .arg(config->getLocalGpsSerialPort())
               .arg(config->getLocalGpsSerialSpeed())
               .arg(serialPortParams);
    }
    localGpsSerial->setText(text);
    localGpsSerial->setEnabled(config->getLocalGpsRunning());

    text = "<strong>Server SYNC:</strong> disabled";
    if(config->getServerSyncEnable() && config->getServerSyncAddress().length() > 0)
        text = QString("<strong>Server SYNC:</strong> %1:%2")
               .arg(config->getServerSyncAddress())
               .arg(config->getServerSyncPort());
    serverSync->setText(text);
    serverSync->setEnabled(config->getServerSyncRunning());
}
