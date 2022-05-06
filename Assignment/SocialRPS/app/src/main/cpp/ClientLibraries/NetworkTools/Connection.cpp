//
// Created by edwardpatch1 on 4/30/22.
//

#include "cnt.h"

cnt::Connection::Connection(NetworkManager::INet4Address* address)
{ this->address = address; }

cnt::Connection::~Connection()
{ }

bool cnt::Connection::InitialiseSocket()
{
    if((sockfd = socket(address->GetSockaddrRef()->sin_family, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        perror("Initialising Socket Failed.");
        return false;
    }

    return true;
}
