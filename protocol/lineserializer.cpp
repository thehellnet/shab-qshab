#include "lineserializer.hpp"
#include "utility.hpp"

LineSerializer::LineSerializer()
{

}

QString LineSerializer::serializeLine(Line line)
{
    QString lineData;

    if(ClientConnectLine* castLine = static_cast<ClientConnectLine*>(&line)) lineData = serializeClientConnectLine(castLine);
    if(ClientUpdateLine* castLine = static_cast<ClientUpdateLine*>(&line)) lineData = serializeClientUpdateLine(castLine);
    if(ClientDisconnectLine* castLine = static_cast<ClientDisconnectLine*>(&line)) lineData = serializeClientDisconnectLine(castLine);
    if(HabPositionLine* castLine = static_cast<HabPositionLine*>(&line)) lineData = serializeHabPositionLine(castLine);
    if(HabImageLine* castLine = static_cast<HabImageLine*>(&line)) lineData = serializeHabImageLine(castLine);
    if(HabTelemetryLine* castLine = static_cast<HabTelemetryLine*>(&line)) lineData = serializeHabTelemetryLine(castLine);

    quint16 checksum = Utility::checksum16(lineData);
    QString chechsumString = QString("%1").arg(checksum, 4, 16, QChar('0')).toUpper();

    return QString("%1|%2").arg(chechsumString).arg(lineData);
}

QString LineSerializer::serializeClientConnectLine(ClientConnectLine* line)
{
    // CC|id|name
    return QString("CC|%1|%2").arg(line->getId()).arg(line->getName());
}

QString LineSerializer::serializeClientUpdateLine(ClientUpdateLine* line)
{
    // CU|latitude|longitude|altitude
    return QString("CU|%1|%2|%3")
            .arg(line->getLatitude())
            .arg(line->getLongitude())
            .arg(line->getAltitude());
}

QString LineSerializer::serializeClientDisconnectLine(ClientDisconnectLine* line)
{
    // 0000|CD|id
    return QString("CD|%1").arg(line->getId());
}

QString LineSerializer::serializeHabPositionLine(HabPositionLine* line)
{
    // 0000|HP|latitude|longitude|altitude
    return QString("HP|%1|%2|%3")
            .arg(line->getLatitude())
            .arg(line->getLongitude())
            .arg(line->getAltitude());
}

QString LineSerializer::serializeHabImageLine(HabImageLine* line)
{
    // 0000|HI|slicenum|slicetot|base64data
    return QString("HI|%1|%2|%3")
            .arg(line->getSliceNum())
            .arg(line->getSliceTot())
            .arg(QString(line->getData().toBase64()));
}

QString LineSerializer::serializeHabTelemetryLine(HabTelemetryLine* line)
{
    // 0000|HT|
    return QString("HI|");
}
