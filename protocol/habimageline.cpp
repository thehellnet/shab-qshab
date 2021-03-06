#include "habimageline.hpp"

HabImageLine::HabImageLine() : Line(Command::HabImage)
{

}

HabImageLine::~HabImageLine()
{

}

QString HabImageLine::serialize()
{
    return QString("HI|%1|%2|%3|%4")
            .arg(timestamp)
            .arg(sliceTot)
            .arg(sliceNum)
            .arg(QString(data.toBase64(QByteArray::Base64UrlEncoding)));
}

long HabImageLine::getTimestamp() const
{
    return timestamp;
}

void HabImageLine::setTimestamp(long value)
{
    timestamp = value;
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
