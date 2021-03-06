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
        static QString addChecksum(QString rawLine);
        static QString randomString(int length);
        static QString getMachineId();
};

#endif // UTILITY_HPP
