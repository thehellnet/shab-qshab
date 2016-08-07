#ifndef DATALOGGER_HPP
#define DATALOGGER_HPP

#include <QObject>

#include "config/configuration.hpp"

class DataLogger : public QObject
{
        Q_OBJECT
    public:
        explicit DataLogger(QObject *parent = 0);

    private:
        Configuration* config;

    signals:
        void imageSaved(QString imagePath);

    public slots:
        void saveLine(QString line);
        void saveImage(QByteArray imageBytes);
};

#endif // DATALOGGER_HPP
