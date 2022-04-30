#include "snt.h"

snt::Connection::Connection(INet4Address* address)
{ this->address = address; }

snt::Connection::~Connection() {}

void snt::Connection::InitialiseSocket()
{
    if((sockfd = socket(address->GetSockaddrRef()->sin_family, SOCK_STREAM, IPPROTO_TCP)) < 0)
        throw "Initialising Socket Failed.";
}