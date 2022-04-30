//
// Created by edwardpatch1 on 4/30/22.
//

#include "cnt.h"

cnt::ClientConnection::ClientConnection(NetworkManager::INet4Address* address) : Connection(address)
{ }

cnt::ClientConnection::~ClientConnection()
{ }

void cnt::ClientConnection::BindSocket()
{
    int errorCode;
    if((errorCode = bind(sockfd, (sockaddr*)address->GetSockaddrRef(), (int)address->GetSocketAddressLengthVal())) < 0)
        throw "Binding Socket Failed";
}

void cnt::ClientConnection::ListenOnSocket(int backlog)
{
    if(listen(sockfd, backlog) < 0)
        throw "Listening on Socket Failed";
}

cnt::ConnectionInstance* cnt::ClientConnection::AcceptClient()
{
    int clientSockfd;
    if((clientSockfd = accept(sockfd, (sockaddr*)address->GetSockaddrRef(), (socklen_t*)address->GetSocketAddressLengthRef())) < 0)
        throw "Accepting Client Failed";

    return new ConnectionInstance(clientSockfd);
}

void cnt::ClientConnection::StartServer(int backlog)
{
    InitialiseSocket();
    BindSocket();
    ListenOnSocket(backlog);
}