#ifndef HABTELEMETRYLINE_HPP
#define HABTELEMETRYLINE_HPP

#include <QString>

#include "line.hpp"
#include "command.hpp"

class HabTelemetryLine : public Line
{
    public:
        HabTelemetryLine();
        ~HabTelemetryLine();

        QString serialize() override;
};

#endif // HABTELEMETRYLINE_HPP
