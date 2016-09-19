#ifndef HABPOSITIONLINE_HPP
#define HABPOSITIONLINE_HPP

#include "line.hpp"
#include "command.hpp"

class HabPositionLine : public Line
{
    public:
        HabPositionLine();
        ~HabPositionLine();

        long getTimestamp() const;
        void setTimestamp(long value);

        QString serialize() override;

        int getFixStatus() const;
        void setFixStatus(int value);

        float getLatitude() const;
        void setLatitude(float value);

        float getLongitude() const;
        void setLongitude(float value);

        float getAltitude() const;
        void setAltitude(float value);

    private:
        long timestamp;

        int fixStatus;
        float latitude;
        float longitude;
        float altitude;
};

#endif // HABPOSITIONLINE_HPP
