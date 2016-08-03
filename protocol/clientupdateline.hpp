#ifndef CLIENTUPDATELINE_HPP
#define CLIENTUPDATELINE_HPP

#include "line.hpp"
#include "command.hpp"

class ClientUpdateLine : public Line
{
    public:
        ClientUpdateLine();
        ~ClientUpdateLine();

        QString serialize() override;

        QString getId() const;
        void setId(const QString&value);

        float getLatitude() const;
        void setLatitude(float value);

        float getLongitude() const;
        void setLongitude(float value);

        float getAltitude() const;
        void setAltitude(float value);

    private:
        QString id;
        float latitude;
        float longitude;
        float altitude;
};

#endif // CLIENTUPDATELINE_HPP
