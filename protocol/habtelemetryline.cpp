#include "habtelemetryline.hpp"

HabTelemetryLine::HabTelemetryLine() : Line(Command::HabTelemetry)
{

}

HabTelemetryLine::~HabTelemetryLine()
{

}

QString HabTelemetryLine::serialize()
{
    return QString("HT|%1|%2|%3")
            .arg(intTemp, 0, 'f', 1)
            .arg(extTemp, 0, 'f', 1)
            .arg(extAlt, 0, 'f', 0);
}
float HabTelemetryLine::getIntTemp() const
{
    return intTemp;
}

void HabTelemetryLine::setIntTemp(float value)
{
    intTemp = value;
}

float HabTelemetryLine::getExtTemp() const
{
    return extTemp;
}

void HabTelemetryLine::setExtTemp(float value)
{
    extTemp = value;
}

float HabTelemetryLine::getExtAlt() const
{
    return extAlt;
}

void HabTelemetryLine::setExtAlt(float value)
{
    extAlt = value;
}
