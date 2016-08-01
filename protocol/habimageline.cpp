#include "habimageline.hpp"

HabImageLine::HabImageLine() : Line(Command::HabImage)
{

}

HabImageLine::~HabImageLine()
{

}

int HabImageLine::getSliceTot() const
{
    return sliceTot;
}

void HabImageLine::setSliceTot(int value)
{
    sliceTot = value;
}

int HabImageLine::getSliceNum() const
{
    return sliceNum;
}

void HabImageLine::setSliceNum(int value)
{
    sliceNum = value;
}

QByteArray HabImageLine::getData() const
{
    return data;
}

void HabImageLine::setData(const QByteArray& value)
{
    data = value;
}
