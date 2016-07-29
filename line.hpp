#ifndef MODEL_HPP
#define MODEL_HPP

#include <QString>

#include "command.hpp"

class Line
{
    public:
        quint16 getChecksum() const;
        void setChecksum(const quint16& value);

        Command getCommand() const;

    protected:
        Line(Command& command);

        quint16 checksum;
        Command command;

};

#endif // MODEL_HPP
