#ifndef HABPOSITIONLINE_HPP
#define HABPOSITIONLINE_HPP

#include "line.hpp"
#include "command.hpp"

class HabPositionLine : public Line
{
    public:
        HabPositionLine();
        ~HabPositionLine();

        float getLatitude() const;
        void setLatitude(float value);

        float getLongitude() const;
        void setLongitude(float value);

        float getAltitude() const;
        void setAltitude(float value);

    private:
        float latitude;
        float longitude;
        float altitude;
};

#endif // HABPOSITIONLINE_HPP
