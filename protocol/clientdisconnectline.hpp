#ifndef CLIENTDISCONNECTLINE_HPP
#define CLIENTDISCONNECTLINE_HPP

#include <QString>

#include "line.hpp"
#include "command.hpp"

class ClientDisconnectLine : public Line
{
    public:
        ClientDisconnectLine();
        ~ClientDisconnectLine();

        QString getId() const;
        void setId(const QString& value);

    private:
        QString id;
};

#endif // CLIENTDISCONNECTLINE_HPP
