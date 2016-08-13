#include "clientconnectline.hpp"

ClientConnectLine::ClientConnectLine() : Line(Command::ClientConnect)
{

}

ClientConnectLine::~ClientConnectLine()
{

}

QString ClientConnectLine::serialize()
{
    return QString("CC|%1|%2")
              .arg(id)
              .arg(name);
}

QString ClientConnectLine::getId() const
{
    return id;
}

void ClientConnectLine::setId(const QString& value)
{
    id = value;
}

QString ClientConnectLine::getName() const
{
    return name;
}

void ClientConnectLine::setName(const QString& value)
{
    name = value;
}
