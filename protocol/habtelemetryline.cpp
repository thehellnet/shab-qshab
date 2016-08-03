#include "habtelemetryline.hpp"

HabTelemetryLine::HabTelemetryLine() : Line(Command::HabTelemetry)
{

}

HabTelemetryLine::~HabTelemetryLine()
{

}

QString HabTelemetryLine::serialize()
{
    rawLine = QString("HT|");
    return rawLine;
}
