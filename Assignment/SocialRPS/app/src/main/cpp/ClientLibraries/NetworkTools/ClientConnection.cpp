//
// Created by edwardpatch1 on 4/30/22.
//

#include "cnt.h"

cnt::ClientConnection::ClientConnection(NetworkManager::INet4Address* address) : Connection(address)
{ }

cnt::ClientConnection::~ClientConnection() { }

void cnt::ClientConnection::BindConnection()
{
    int errorCode;
    if((errorCode = bind(sockfd, (sockaddr*)address->GetSockaddrRef(), (int)address->GetSocketAddressLengthVal())) < 0)
        throw "Binding Socket Failed";
}

cnt::ConnectionInstance* cnt::ClientConnection::ConnectToServer()
{
    InitialiseSocket();
    BindConnection();

    return new cnt::ConnectionInstance(sockfd);
}