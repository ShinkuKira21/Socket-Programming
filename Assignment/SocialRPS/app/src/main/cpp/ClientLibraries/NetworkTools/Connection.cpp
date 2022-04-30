//
// Created by edwardpatch1 on 4/30/22.
//

#include "cnt.h"

cnt::Connection::Connection(NetworkManager::INet4Address* address)
{ this->address = address; }

cnt::Connection::~Connection() {}

void cnt::Connection::InitialiseSocket()
{
    if((sockfd = socket(address->GetSockaddrRef()->sin_family, SOCK_STREAM, IPPROTO_TCP)) < 0)
        throw "Initialising Socket Failed.";
}
