#include "clientupdateline.hpp"

ClientUpdateLine::ClientUpdateLine() : Line(Command::ClientUpdate)
{

}

ClientUpdateLine::~ClientUpdateLine()
{

}

QString ClientUpdateLine::serialize()
{
    return QString("CU|%1|%2|%3|%4")
            .arg(id)
            .arg(latitude)
            .arg(longitude)
            .arg(altitude);
}

QString ClientUpdateLine::getId() const
{
    return id;
}

void ClientUpdateLine::setId(const QString&value)
{
    id = value;
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
