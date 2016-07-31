#include "clientdisconnectline.hpp"

ClientDisconnectLine::ClientDisconnectLine() : Line(Command::ClientDisconnect)
{

}

QString ClientDisconnectLine::getId() const
{
    return id;
}

void ClientDisconnectLine::setId(const QString& value)
{
    id = value;
}
