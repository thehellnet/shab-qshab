#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <QObject>

class Configuration : public QObject
{
        Q_OBJECT

    public:
        explicit Configuration(QObject *parent = 0);

        bool getHabRunning() const;
        void setHabRunning(bool value);

        bool getLocalGpsRunning() const;
        void setLocalGpsRunning(bool value);

    private:
        bool habRunning;
        bool localGpsRunning;

};

#endif // CONFIGURATION_HPP
