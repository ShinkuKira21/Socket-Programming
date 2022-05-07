//
// Created by edwardpatch1 on 4/30/22.
//

#include "cnt.h"

cnt::ClientConnection::ClientConnection(NetworkManager::INet4Address* address) : Connection(address)
{ }

cnt::ClientConnection::~ClientConnection() { }

bool cnt::ClientConnection::BindConnection()
{
    int errorCode;
    if((errorCode = bind(sockfd, (sockaddr*)address->GetSockaddrRef(), (int)address->GetSocketAddressLengthVal())) < 0)
        return false;

    return true;
}

cnt::ConnectionInstance* cnt::ClientConnection::ConnectToServer()
{
    if(!InitialiseSocket()) return nullptr;
    if(!BindConnection()) return nullptr;
    return new cnt::ConnectionInstance(sockfd);
}