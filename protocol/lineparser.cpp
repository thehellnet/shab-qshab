#include <QString>
#include <QStringList>
#include <QByteArray>

#include "protocol/lineparser.hpp"
#include "protocol/command.hpp"
#include "utility.hpp"

LineParser::LineParser()
{

}

Line* LineParser::parseLine(QString rawLine)
{
    QStringList items = rawLine.split('|');

    if(Utility::checksum16(rawLine.right(5)) != items[0].toUInt(nullptr, 16))
        return nullptr;

    if(items[1] == "HP") return parseHabPosition(items);
    if(items[1] == "HI") return parseHabImage(items);
    if(items[1] == "HT") return parseHabTelemetry(items);
    if(items[1] == "CC") return parseClientConnect(items);
    if(items[1] == "CU") return parseClientUpdate(items);
    if(items[1] == "CD") return parseClientDisconnect(items);

    return nullptr;
}

HabPositionLine* LineParser::parseHabPosition(QStringList items)
{
    // 0000|HP|latitude|longitude|altitude
    if(items.size() != 4 || items[2] != "HP")
        return nullptr;

    HabPositionLine* line = new HabPositionLine();
    line->setLatitude(items[3].toFloat());
    line->setLongitude(items[4].toFloat());
    line->setAltitude(items[5].toFloat());
    return line;
}

HabImageLine* LineParser::parseHabImage(QStringList items)
{
    // 0000|HP|slicenum|slicetot|base64data
    if(items.size() != 5 || items[2] != "HI")
        return nullptr;

    HabImageLine* line = new HabImageLine();
    line->setSliceTot(items[3].toInt());
    line->setSliceNum(items[4].toInt());
    line->setData(QByteArray::fromBase64(items[5].toLatin1()));
    return line;
}

HabTelemetryLine* LineParser::parseHabTelemetry(QStringList items)
{
    // 0000|HP|
    if(items.size() != 4 || items[2] != "HT")
        return nullptr;

    HabTelemetryLine* line = new HabTelemetryLine();

    return line;
}

ClientConnectLine* LineParser::parseClientConnect(QStringList items)
{
    // 0000|CC|id|name
    if(items.size() != 4 || items[2] != "CC")
        return nullptr;

    ClientConnectLine* line = new ClientConnectLine();
    line->setId(items[3]);
    line->setName(items[4]);
    return line;
}

ClientUpdateLine* LineParser::parseClientUpdate(QStringList items)
{
    // 0000|CU|latitude|longitude|altitude
    if(items.size() != 5 || items[2] != "CU")
        return nullptr;

    ClientUpdateLine* line = new ClientUpdateLine();
    line->setLatitude(items[3].toFloat());
    line->setLongitude(items[4].toFloat());
    line->setAltitude(items[5].toFloat());
    return line;
}

ClientDisconnectLine* LineParser::parseClientDisconnect(QStringList items)
{
    // 0000|CD|id
    if(items.size() != 3 || items[2] != "CD")
        return nullptr;

    ClientDisconnectLine* line = new ClientDisconnectLine();
    line->setId(items[3]);
    return line;
}
