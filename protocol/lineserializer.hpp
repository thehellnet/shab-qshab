#ifndef LINESERIALIZER_HPP
#define LINESERIALIZER_HPP

#include <QString>

#include "protocol/lineparser.hpp"
#include "protocol/line.hpp"
#include "protocol/habpositionline.hpp"
#include "protocol/habimageline.hpp"
#include "protocol/habtelemetryline.hpp"
#include "protocol/clientconnectline.hpp"
#include "protocol/clientupdateline.hpp"
#include "protocol/clientdisconnectline.hpp"

class LineSerializer
{
    public:
        LineSerializer();

        static QString serializeLine(Line line);

    private:
        static QString serializeClientConnectLine(ClientConnectLine* line);
        static QString serializeClientUpdateLine(ClientUpdateLine* line);
        static QString serializeClientDisconnectLine(ClientDisconnectLine* line);
        static QString serializeHabPositionLine(HabPositionLine* line);
        static QString serializeHabImageLine(HabImageLine* line);
        static QString serializeHabTelemetryLine(HabTelemetryLine* line);
};

#endif // LINESERIALIZER_HPP
