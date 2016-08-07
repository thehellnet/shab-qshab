#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QString>
#include <QGeoCoordinate>

class Client
{
    public:
        Client();

        QString getId() const;
        void setId(const QString&value);

        QString getName() const;
        void setName(const QString&value);

        QGeoCoordinate getPosition() const;
        void setPosition(const QGeoCoordinate&value);

    private:
        QString id;
        QString name;
        QGeoCoordinate position;
};

#endif // CLIENT_HPP
