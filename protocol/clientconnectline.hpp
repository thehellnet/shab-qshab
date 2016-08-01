#ifndef CLIENTCONNECTLINE_HPP
#define CLIENTCONNECTLINE_HPP

#include <QString>

#include "line.hpp"
#include "command.hpp"

class ClientConnectLine : public Line
{
    public:
        ClientConnectLine();
        ~ClientConnectLine();

        QString getId() const;
        void setId(const QString& value);

        QString getName() const;
        void setName(const QString& value);

    private:
        QString id;
        QString name;
};

#endif // CLIENTCONNECTLINE_HPP
