#include "protocol/line.hpp"

Line::Line(Command command)
{
    this->command = command;
}

QString Line::serialize()
{
    rawLine = "";
    return rawLine;
}

QString Line::getRawLine() const
{
    return rawLine;
}

void Line::setRawLine(const QString& value)
{
    rawLine = value;
}

Command Line::getCommand() const
{
    return command;
}
