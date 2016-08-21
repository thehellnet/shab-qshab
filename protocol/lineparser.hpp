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

        static Line* parseLine(QString rawLine);

    private:
        static HabPositionLine* parseHabPosition(QStringList items);
        static HabImageLine* parseHabImage(QStringList items);
        static HabTelemetryLine* parseHabTelemetry(QStringList items);
        static ClientConnectLine* parseClientConnect(QStringList items);
        static ClientUpdateLine* parseClientUpdate(QStringList items);
        static ClientDisconnectLine* parseClientDisconnect(QStringList items);
};

#endif // LINEPARSER_HPP
