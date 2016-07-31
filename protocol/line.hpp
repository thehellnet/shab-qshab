#ifndef MODEL_HPP
#define MODEL_HPP

#include <QString>

#include "command.hpp"

class Line
{
    public:
        Command getCommand() const;

        QString getRawLine() const;
        void setRawLine(const QString& value);

    protected:
        Line(Command command);

    private:
        Command command;
        QString rawLine;
};

#endif // MODEL_HPP
