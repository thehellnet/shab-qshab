#include "habpositionline.hpp"

HabPositionLine::HabPositionLine() : Line(Command::HabPosition)
{

}

HabPositionLine::~HabPositionLine()
{

}

QString HabPositionLine::serialize()
{
    return QString("HP|%1|%2|%3|%4|%5")
            .arg(timestamp)
            .arg(fixStatus)
            .arg(latitude)
            .arg(longitude)
            .arg(altitude);
}

long HabPositionLine::getTimestamp() const
{
    return timestamp;
}

void HabPositionLine::setTimestamp(long value)
{
    timestamp = value;
}

int HabPositionLine::getFixStatus() const
{
    return fixStatus;
}

void HabPositionLine::setFixStatus(int value)
{
    fixStatus = value;
}

float HabPositionLine::getLatitude() const
{
    return latitude;
}

void HabPositionLine::setLatitude(float value)
{
    latitude = value;
}

float HabPositionLine::getLongitude() const
{
    return longitude;
}

void HabPositionLine::setLongitude(float value)
{
    longitude = value;
}

float HabPositionLine::getAltitude() const
{
    return altitude;
}

void HabPositionLine::setAltitude(float value)
{
    altitude = value;
}
