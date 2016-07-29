#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <QString>

class Utility
{
    public:
        Utility();

        static QString serialPortParams(QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits);
};

#endif // UTILITY_HPP
