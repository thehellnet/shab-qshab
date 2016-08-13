#ifndef GPSHANDLER_HPP
#define GPSHANDLER_HPP

#include <QObject>
#include <QNmeaPositionInfoSource>
#include <QSerialPort>

#include "config/configuration.hpp"

class GPSHandler : public QObject
{
        Q_OBJECT

    public:
        explicit GPSHandler(QObject *parent = 0);
        ~GPSHandler();

        void start();
        void stop();

    private:
        Configuration* config;
        QNmeaPositionInfoSource* source;
        QSerialPort* serial;

    signals:
        void newPosition(QGeoCoordinate position);

    private slots:
        void positionUpdated(QGeoPositionInfo positionInfo);
};

#endif // GPSHANDLER_HPP
