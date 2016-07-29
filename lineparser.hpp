#ifndef LINEPARSER_HPP
#define LINEPARSER_HPP

#include <QString>

#include "line.hpp"

class LineParser
{
    public:
        LineParser();

        static Line parseLine(QString rawLine);
};

#endif // LINEPARSER_HPP
