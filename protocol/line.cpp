#include "protocol/line.hpp"

Line::Line(Command command)
{
    this->command = command;
}

Line::~Line()
{

}

QString Line::serialize()
{
    return "";
}

Command Line::getCommand() const
{
    return command;
}
