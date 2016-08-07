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
    rawLine = rawLine.simplified();
    QStringList items = rawLine.split('|');

    if(Utility::checksum16(rawLine.mid(5)) != items[0].toUInt(nullptr, 16)
            || items.count() < 2)
        return nullptr;

    if(items[1] == "HP") return parseHabPosition(rawLine, items);
    if(items[1] == "HI") return parseHabImage(rawLine, items);
    if(items[1] == "HT") return parseHabTelemetry(rawLine, items);
    if(items[1] == "CC") return parseClientConnect(rawLine, items);
    if(items[1] == "CU") return parseClientUpdate(rawLine, items);
    if(items[1] == "CD") return parseClientDisconnect(rawLine, items);

    return nullptr;
}

HabPositionLine* LineParser::parseHabPosition(QString rawLine, QStringList items)
{
    // 0000|HP|latitude|longitude|altitude
    if(items.size() != 5 || items[1] != "HP")
        return nullptr;

    HabPositionLine* line = new HabPositionLine();
    line->setRawLine(rawLine);
    line->setLatitude(items[2].toFloat());
    line->setLongitude(items[3].toFloat());
    line->setAltitude(items[4].toFloat());
    return line;
}

HabImageLine* LineParser::parseHabImage(QString rawLine, QStringList items)
{
    // 0000|HI|slicenum|slicetot|base64data
    if(items.size() != 5 || items[1] != "HI")
        return nullptr;

    HabImageLine* line = new HabImageLine();
    line->setRawLine(rawLine);
    line->setSliceTot(items[2].toInt());
    line->setSliceNum(items[3].toInt());
    line->setData(QByteArray::fromBase64(items[4].toLatin1()));
    return line;
}

HabTelemetryLine* LineParser::parseHabTelemetry(QString rawLine, QStringList items)
{
    // 0000|HT|
    if(items.size() != 2 || items[1] != "HT")
        return nullptr;

    HabTelemetryLine* line = new HabTelemetryLine();
    line->setRawLine(rawLine);
    return line;
}

ClientConnectLine* LineParser::parseClientConnect(QString rawLine, QStringList items)
{
    // 0000|CC|id|name
    if(items.size() != 4 || items[1] != "CC")
        return nullptr;

    ClientConnectLine* line = new ClientConnectLine();
    line->setRawLine(rawLine);
    line->setId(items[2]);
    line->setName(items[3]);
    return line;
}

ClientUpdateLine* LineParser::parseClientUpdate(QString rawLine, QStringList items)
{
    // 0000|CU|id|latitude|longitude|altitude
    if(items.size() != 6 || items[1] != "CU")
        return nullptr;

    ClientUpdateLine* line = new ClientUpdateLine();
    line->setRawLine(rawLine);
    line->setId(items[2]);
    line->setLatitude(items[3].toFloat());
    line->setLongitude(items[4].toFloat());
    line->setAltitude(items[5].toFloat());
    return line;
}

ClientDisconnectLine* LineParser::parseClientDisconnect(QString rawLine, QStringList items)
{
    // 0000|CD|id
    if(items.size() != 3 || items[1] != "CD")
        return nullptr;

    ClientDisconnectLine* line = new ClientDisconnectLine();
    line->setRawLine(rawLine);
    line->setId(items[2]);
    return line;
}
