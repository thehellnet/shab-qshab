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

        float getIntTemp() const;
        void setIntTemp(float value);

        float getExtTemp() const;
        void setExtTemp(float value);

        float getExtAlt() const;
        void setExtAlt(float value);

    private:
        float intTemp;
        float extTemp;
        float extAlt;
};

#endif // HABTELEMETRYLINE_HPP
