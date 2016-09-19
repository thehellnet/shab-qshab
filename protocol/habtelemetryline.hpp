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

        long getTimestamp() const;
        void setTimestamp(long value);

        float getIntTemp() const;
        void setIntTemp(float value);

        float getExtTemp() const;
        void setExtTemp(float value);

        float getExtAlt() const;
        void setExtAlt(float value);

    private:
        long timestamp;

        float intTemp;
        float extTemp;
        float extAlt;
};

#endif // HABTELEMETRYLINE_HPP
