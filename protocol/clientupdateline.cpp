#include "clientupdateline.hpp"

ClientUpdateLine::ClientUpdateLine() : Line(Command::ClientUpdate)
{

}

ClientUpdateLine::~ClientUpdateLine()
{

}

QString ClientUpdateLine::serialize()
{
    rawLine = QString("CU|%1|%2|%3")
            .arg(latitude)
            .arg(longitude)
            .arg(altitude);
    return rawLine;
}

float ClientUpdateLine::getLatitude() const
{
    return latitude;
}

void ClientUpdateLine::setLatitude(float value)
{
    latitude = value;
}

float ClientUpdateLine::getLongitude() const
{
    return longitude;
}

void ClientUpdateLine::setLongitude(float value)
{
    longitude = value;
}

float ClientUpdateLine::getAltitude() const
{
    return altitude;
}

void ClientUpdateLine::setAltitude(float value)
{
    altitude = value;
}
