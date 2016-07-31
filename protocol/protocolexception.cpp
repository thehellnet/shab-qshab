#include "protocolexception.hpp"

ProtocolException::ProtocolException()
{

}

void ProtocolException::raise() const
{
    throw *this;
}

ProtocolException* ProtocolException::clone() const
{
    return new ProtocolException(*this);
}
