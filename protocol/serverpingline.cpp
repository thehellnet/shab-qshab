#include "serverpingline.hpp"

ServerPingLine::ServerPingLine() : Line(Command::ServerPing)
{

}

ServerPingLine::~ServerPingLine()
{

}

QString ServerPingLine::serialize()
{
    return QString("SP|%1")
            .arg(timestamp);
}

unsigned long long ServerPingLine::getTimestamp() const
{
    return timestamp;
}

void ServerPingLine::setTimestamp(qint64 value)
{
    timestamp = value;
}

