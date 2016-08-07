#include "client.hpp"

Client::Client()
{

}

QString Client::getId() const
{
    return id;
}

void Client::setId(const QString&value)
{
    id = value;
}

QString Client::getName() const
{
    return name;
}

void Client::setName(const QString&value)
{
    name = value;
}

QGeoCoordinate Client::getPosition() const
{
    return position;
}

void Client::setPosition(const QGeoCoordinate&value)
{
    position = value;
}
