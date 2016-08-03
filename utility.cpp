#include <QSerialPort>
#include <QCryptographicHash>

#include "utility.hpp"

Utility::Utility()
{

}

QString Utility::serialPortParams(QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    QString dataBitsString;
    QString parityString;
    QString stopBitsString;

    switch(dataBits) {
        case QSerialPort::Data5:
            dataBitsString = "5";
            break;
        case QSerialPort::Data6:
            dataBitsString = "6";
            break;
        case QSerialPort::Data7:
            dataBitsString = "7";
            break;
        case QSerialPort::Data8:
            dataBitsString = "8";
            break;
        default:
            dataBitsString = "#";
    }

    switch(parity) {
        case QSerialPort::NoParity:
            parityString = "N";
            break;
        case QSerialPort::OddParity:
            parityString = "O";
            break;
        case QSerialPort::EvenParity:
            parityString = "E";
            break;
        case QSerialPort::SpaceParity:
            parityString = "S";
            break;
        case QSerialPort::MarkParity:
            parityString = "M";
            break;
        default:
            dataBitsString = "#";
    }

    switch(stopBits) {
        case QSerialPort::OneStop:
            stopBitsString = "1";
            break;
        case QSerialPort::OneAndHalfStop:
            stopBitsString = "1.5";
            break;
        case QSerialPort::TwoStop:
            stopBitsString = "2";
            break;
        default:
            dataBitsString = "#";
    }

    return QString("%1-%2-%3")
            .arg(dataBitsString)
            .arg(parityString)
            .arg(stopBits);
}

quint16 Utility::checksum16(QString rawData)
{
    unsigned int ret = 0;

    for(int i=0; i<rawData.length(); i++) {
        ret += (unsigned char) rawData.at(i).toLatin1();
        ret %= 0xFFFF;
    }

    return (quint16) ret;
}

QString Utility::randomString(int length)
{
    QString randomString;

    const QString possibleCharacters("abcdefghijklmnopqrstuvwxyz0123456789");

    for(int i=0; i<length; ++i)
        randomString.append(possibleCharacters.at(qrand() % possibleCharacters.length()));

    return randomString;
}

QString Utility::getMachineId()
{
    QString data = randomString(16)
                   + QSysInfo::buildAbi()
                   + QSysInfo::buildCpuArchitecture()
                   + QSysInfo::currentCpuArchitecture()
                   + QSysInfo::kernelType()
                   + QSysInfo::kernelVersion()
                   + QString(QSysInfo::macVersion())
                   + QSysInfo::machineHostName()
                   + QSysInfo::prettyProductName()
                   + QSysInfo::productType()
                   + QSysInfo::productVersion()
                   + QString(QSysInfo::windowsVersion());

    return QCryptographicHash::hash(data.toLatin1(), QCryptographicHash::Sha512)
            .toHex()
            .left(16);
}
