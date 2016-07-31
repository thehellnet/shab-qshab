#include "habpositionline.hpp"

HabPositionLine::HabPositionLine() : Line(Command::HabPosition)
{

}

float HabPositionLine::getLatitude() const
{
    return latitude;
}

void HabPositionLine::setLatitude(float value)
{
    latitude = value;
}

float HabPositionLine::getLongitude() const
{
    return longitude;
}

void HabPositionLine::setLongitude(float value)
{
    longitude = value;
}

float HabPositionLine::getAltitude() const
{
    return altitude;
}

void HabPositionLine::setAltitude(float value)
{
    altitude = value;
}
