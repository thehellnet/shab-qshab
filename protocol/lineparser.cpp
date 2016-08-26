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

    if(items[1] == "HP") return parseHabPosition(items);
    if(items[1] == "HI") return parseHabImage(items);
    if(items[1] == "HT") return parseHabTelemetry(items);
    if(items[1] == "CC") return parseClientConnect(items);
    if(items[1] == "CU") return parseClientUpdate(items);
    if(items[1] == "CD") return parseClientDisconnect(items);
    if(items[1] == "SP") return parseServerPing(items);

    return nullptr;
}

HabPositionLine* LineParser::parseHabPosition(QStringList items)
{
    // 0000|HP|fixstatus|latitude|longitude|altitude
    if(items.size() != 6 || items[1] != "HP")
        return nullptr;

    HabPositionLine* line = new HabPositionLine();
    line->setFixStatus(items[2].toInt());
    line->setLatitude(items[3].toFloat());
    line->setLongitude(items[4].toFloat());
    line->setAltitude(items[5].toFloat());
    return line;
}

HabImageLine* LineParser::parseHabImage(QStringList items)
{
    // 0000|HI|slicenum|slicetot|base64data
    if(items.size() != 5 || items[1] != "HI")
        return nullptr;

    HabImageLine* line = new HabImageLine();
    line->setSliceTot(items[2].toInt());
    line->setSliceNum(items[3].toInt());
    line->setData(QByteArray::fromBase64(items[4].toLatin1(), QByteArray::Base64UrlEncoding));
    return line;
}

HabTelemetryLine* LineParser::parseHabTelemetry(QStringList items)
{
    // 0000|HT|int_temp|ext_temp|ext_alt
    if(items.size() != 5 || items[1] != "HT")
        return nullptr;

    HabTelemetryLine* line = new HabTelemetryLine();
    line->setIntTemp(items[2].toFloat());
    line->setExtTemp(items[3].toFloat());
    line->setExtAlt(items[4].toFloat());
    return line;
}

ClientConnectLine* LineParser::parseClientConnect(QStringList items)
{
    // 0000|CC|id|name
    if(items.size() != 4 || items[1] != "CC")
        return nullptr;

    ClientConnectLine* line = new ClientConnectLine();
    line->setId(items[2]);
    line->setName(items[3]);
    return line;
}

ClientUpdateLine* LineParser::parseClientUpdate(QStringList items)
{
    // 0000|CU|id|latitude|longitude|altitude
    if(items.size() != 6 || items[1] != "CU")
        return nullptr;

    ClientUpdateLine* line = new ClientUpdateLine();
    line->setId(items[2]);
    line->setLatitude(items[3].toFloat());
    line->setLongitude(items[4].toFloat());
    line->setAltitude(items[5].toFloat());
    return line;
}

ClientDisconnectLine* LineParser::parseClientDisconnect(QStringList items)
{
    // 0000|CD|id
    if(items.size() != 3 || items[1] != "CD")
        return nullptr;

    ClientDisconnectLine* line = new ClientDisconnectLine();
    line->setId(items[2]);
    return line;
}

ServerPingLine* LineParser::parseServerPing(QStringList items)
{
    // 0000|SP|timestamp
    if(items.size() != 3 || items[1] != "SP")
        return nullptr;

    ServerPingLine* line = new ServerPingLine();
    line->setTimestamp(items[2].toULongLong());
    return line;
}
