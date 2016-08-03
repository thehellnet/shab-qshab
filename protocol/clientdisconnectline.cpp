#include "clientdisconnectline.hpp"

ClientDisconnectLine::ClientDisconnectLine() : Line(Command::ClientDisconnect)
{

}

ClientDisconnectLine::~ClientDisconnectLine()
{

}

QString ClientDisconnectLine::serialize()
{
    rawLine = QString("CD|%1")
            .arg(id);
    return rawLine;
}

QString ClientDisconnectLine::getId() const
{
    return id;
}

void ClientDisconnectLine::setId(const QString& value)
{
    id = value;
}
