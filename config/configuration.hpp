#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <QObject>
#include <QString>
#include <QtSerialPort/QtSerialPort>

class Configuration
{
    private:
        Configuration();
        static Configuration* instance;

    public:
        static Configuration* getInstance();

        bool getHabRunning() const;
        void setHabRunning(bool value);

        bool getLocalGpsRunning() const;
        void setLocalGpsRunning(bool value);

        bool getServerSyncRunning() const;
        void setServerSyncRunning(bool value);

        QString getHabSerialPort() const;
        void setHabSerialPort(const QString& value);

        QSerialPort::BaudRate getHabSerialSpeed() const;
        void setHabSerialSpeed(const QSerialPort::BaudRate& value);

        bool getLocalGpsSerialEnable() const;
        void setLocalGpsSerialEnable(bool value);

        QString getLocalGpsSerialPort() const;
        void setLocalGpsSerialPort(const QString& value);

        QSerialPort::BaudRate getLocalGpsSerialSpeed() const;
        void setLocalGpsSerialSpeed(const QSerialPort::BaudRate& value);

        QSerialPort::FlowControl getLocalGpsSerialFlowControl() const;
        void setLocalGpsSerialFlowControl(const QSerialPort::FlowControl& value);

        QSerialPort::Parity getLocalGpsSerialParity() const;
        void setLocalGpsSerialParity(const QSerialPort::Parity& value);

        QSerialPort::DataBits getLocalGpsSerialDataBits() const;
        void setLocalGpsSerialDataBits(const QSerialPort::DataBits& value);

        QSerialPort::StopBits getLocalGpsSerialStopBits() const;
        void setLocalGpsSerialStopBits(const QSerialPort::StopBits& value);

        bool getServerSyncEnable() const;
        void setServerSyncEnable(bool value);

        QString getServerSyncAddress() const;
        void setServerSyncAddress(const QString& value);

        quint16 getServerSyncPort() const;
        void setServerSyncPort(const quint16& value);

        QString getServerSyncName() const;
        void setServerSyncName(const QString&value);

        bool getLogRawEnable() const;
        void setLogRawEnable(bool value);

        QString getLogRawPath() const;
        void setLogRawPath(const QString& value);

        bool getLogImagesEnable() const;
        void setLogImagesEnable(bool value);

        QString getLogImagesPath() const;
        void setLogImagesPath(const QString& value);

    private:
        bool habRunning;
        bool localGpsRunning;
        bool serverSyncRunning;

        QString habSerialPort;
        QSerialPort::BaudRate habSerialSpeed;

        bool localGpsSerialEnable;
        QString localGpsSerialPort;
        QSerialPort::BaudRate localGpsSerialSpeed;
        QSerialPort::FlowControl localGpsSerialFlowControl;
        QSerialPort::Parity localGpsSerialParity;
        QSerialPort::DataBits localGpsSerialDataBits;
        QSerialPort::StopBits localGpsSerialStopBits;

        bool serverSyncEnable;
        QString serverSyncAddress;
        quint16 serverSyncPort;
        QString serverSyncName;

        bool logRawEnable;
        QString logRawPath;
        bool logImagesEnable;
        QString logImagesPath;
};

#endif // CONFIGURATION_HPP
