#include <QString>
#include <QStringList>

#include "lineparser.hpp"
#include "command.hpp"

LineParser::LineParser()
{

}

Line LineParser::parseLine(QString rawLine)
{
    quint16 checksum;
    Command command;

    QStringList items = rawLine.split('|');
    checksum = items[0].toUInt(nullptr, 16);

    switch(items[1]) {
        case "HP":
            command = Command::HabPosition;
            break;
        case "HI":
            command = Command::HabImage;
            break;
        case "HT":
            command = Command::HabPosition;
            break;
        case "CC":
            command = Command::ClientConnect;
            break;
        case "CU":
            command = Command::ClientUpdate;
            break;
        case "CD":
            command = Command::ClientDisconnect;
            break;
    }
}
