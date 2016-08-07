#include <QFile>
#include <QDir>
#include <QDateTime>

#include "datalogger.hpp"
#include "config/configurationcontroller.hpp"

DataLogger::DataLogger(QObject *parent) : QObject(parent)
{
    config = Configuration::getInstance();
}

void DataLogger::saveLine(QString line)
{
    if(!config->getLogRawEnable())
        return;

    QFile file(config->getLogRawPath());
    file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
    file.write(line.toLatin1());
    file.close();
}

void DataLogger::saveImage(QByteArray imageBytes)
{
    if(!config->getLogImagesEnable())
        return;

    QDateTime dateTime = QDateTime::currentDateTime();

    QString fileName = "shab_image-" + dateTime.toString("yyyyMMddHHmmss") + ".jpg";
    QString fileNamePath = QDir(config->getLogImagesPath()).filePath(fileName);

    QFile file(fileNamePath);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    file.write(imageBytes);
    file.close();

    emit imageSaved(fileNamePath);
}
