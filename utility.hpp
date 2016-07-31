#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <QString>
#include <QSerialPort>

class Utility
{
    public:
        Utility();

        static QString serialPortParams(QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits);
        static quint16 checksum16(QString rawData);
};

#endif // UTILITY_HPP
