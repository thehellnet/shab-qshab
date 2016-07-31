#include "line.hpp"

Line::Line(Command command)
{
    this->command = command;
}

Command Line::getCommand() const
{
    return command;
}
