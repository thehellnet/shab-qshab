#ifndef HABHANDLER_HPP
#define HABHANDLER_HPP

#include <QObject>
#include <QString>
#include <QSerialPort>

#include "config/configuration.hpp"

class HabHandler : public QObject
{
        Q_OBJECT
    public:
        explicit HabHandler(QObject *parent = 0);
        ~HabHandler();

        bool isRunning() const;
        void start();
        void stop();

    private:
        bool running;
        Configuration* config;
        QSerialPort* serial;

    signals:
        void newLine(QString line);

    private slots:
        void readLine();
};

#endif // HABHANDLER_HPP
