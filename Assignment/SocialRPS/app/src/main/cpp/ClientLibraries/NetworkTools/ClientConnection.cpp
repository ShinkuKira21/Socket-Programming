//
// Created by edwardpatch1 on 4/30/22.
//

#include "cnt.h"

cnt::ClientConnection::ClientConnection(NetworkManager::INet4Address* address) : Connection(address)
{ }

cnt::ClientConnection::~ClientConnection() { }

int cnt::ClientConnection::BindConnection()
{
    int errorCode;
    if((errorCode = bind(sockfd, (sockaddr*)address->GetSockaddrRef(), (int)address->GetSocketAddressLengthVal())) < 0)
        perror("Binding Socket Failed");

    return errorCode;
}

cnt::ConnectionInstance* cnt::ClientConnection::ConnectToServer()
{
    if(InitialiseSocket() == false) return nullptr;
    if(BindConnection() == false) return nullptr;
    return new cnt::ConnectionInstance(sockfd);
}