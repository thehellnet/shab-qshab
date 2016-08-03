#ifndef LINE_HPP
#define LINE_HPP

#include <QString>

#include "protocol/command.hpp"

class Line
{
    public:
        virtual QString serialize();

        Command getCommand() const;

        QString getRawLine() const;
        void setRawLine(const QString& value);

    protected:
        QString rawLine;

        Line(Command command);

    private:
        Command command;
};

#endif // LINE_HPP
