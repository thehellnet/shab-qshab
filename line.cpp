#include "line.hpp"

Line::Line(Command& command)
{
    this->command = command;
}

quint16 Line::getChecksum() const
{
    return checksum;
}

void Line::setChecksum(const quint16& value)
{
    checksum = value;
}

Command Line::getCommand() const
{
    return command;
}
