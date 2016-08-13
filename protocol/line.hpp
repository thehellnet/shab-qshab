#ifndef LINE_HPP
#define LINE_HPP

#include <QString>

#include "protocol/command.hpp"

class Line
{
    public:
        virtual ~Line();
        virtual QString serialize();

        Command getCommand() const;

    protected:
        Line(Command command);

    private:
        Command command;
};

#endif // LINE_HPP
