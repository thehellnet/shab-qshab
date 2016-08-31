#ifndef SERVERPINGLINE_HPP
#define SERVERPINGLINE_HPP

#include "line.hpp"
#include "command.hpp"

class ServerPingLine : public Line
{
    public:
        ServerPingLine();
        ~ServerPingLine();

        QString serialize() override;

        unsigned long long getTimestamp() const;
        void setTimestamp(qint64 value);

    private:
        unsigned long long timestamp;
};

#endif // SERVERPINGLINE_HPP
