#include "hab.hpp"

Hab::Hab()
{

}

int Hab::getFixStatus() const
{
    return fixStatus;
}

void Hab::setFixStatus(int value)
{
    fixStatus = value;
}

double Hab::getLatitude() const
{
    return latitude;
}

void Hab::setLatitude(double value)
{
    latitude = value;
}

double Hab::getLongitude() const
{
    return longitude;
}

void Hab::setLongitude(double value)
{
    longitude = value;
}

double Hab::getAltitude() const
{
    return altitude;
}

void Hab::setAltitude(double value)
{
    altitude = value;
}

int Hab::getSliceTot() const
{
    return sliceTot;
}

void Hab::setSliceTot(int value)
{
    sliceTot = value;
}

int Hab::getSliceNum() const
{
    return sliceNum;
}

void Hab::setSliceNum(int value)
{
    sliceNum = value;
}

QByteArray Hab::getImageData() const
{
    return imageData;
}

void Hab::clearImageData()
{
    imageData.clear();
}

void Hab::appendImageData(const QByteArray& value)
{
    imageData.append(value);
}
