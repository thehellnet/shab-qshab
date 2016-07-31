#ifndef PROTOCOLEXCEPTION_HPP
#define PROTOCOLEXCEPTION_HPP

#include <QException>

class ProtocolException : public QException
{
    public:
        ProtocolException();

        void raise() const;
        ProtocolException* clone() const;
};

#endif // PROTOCOLEXCEPTION_HPP
