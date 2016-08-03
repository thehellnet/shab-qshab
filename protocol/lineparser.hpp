#ifndef LINEPARSER_HPP
#define LINEPARSER_HPP

#include <QString>

#include "protocol/line.hpp"
#include "protocol/habpositionline.hpp"
#include "protocol/habimageline.hpp"
#include "protocol/habtelemetryline.hpp"
#include "protocol/clientconnectline.hpp"
#include "protocol/clientupdateline.hpp"
#include "protocol/clientdisconnectline.hpp"

class LineParser
{
    public:
        LineParser();

        static Line parseLine(QString rawLine);

    private:
        static HabPositionLine parseHabPosition(QString rawLine, QStringList items);
        static HabImageLine parseHabImage(QString rawLine, QStringList items);
        static HabTelemetryLine parseHabTelemetry(QString rawLine, QStringList items);
        static ClientConnectLine parseClientConnect(QString rawLine, QStringList items);
        static ClientUpdateLine parseClientUpdate(QString rawLine, QStringList items);
        static ClientDisconnectLine parseClientDisconnect(QString rawLine, QStringList items);
};

#endif // LINEPARSER_HPP
