#ifndef MODEL_HPP
#define MODEL_HPP

#include <QString>

#include "command.hpp"

class Line
{
    public:
        Command getCommand() const;

    protected:
        Line(Command command);

        Command command;
};

#endif // MODEL_HPP
