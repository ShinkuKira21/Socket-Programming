#include "snt.h"

snt::ServerConnection::ServerConnection(INet4Address* address) : Connection(address)
{ }

snt::ServerConnection::~ServerConnection()
{ }

void snt::ServerConnection::BindSocket()
{ 
    int errorCode;
    if((errorCode = bind(sockfd, (sockaddr*)address->GetSockaddrRef(), (int)address->GetSocketAddressLengthVal())) < 0)
        throw "Binding Socket Failed";
}

void snt::ServerConnection::ListenOnSocket(int backlog)
{
    if(listen(sockfd, backlog) < 0)
        throw "Listening on Socket Failed";
}

snt::ConnectionInstance* snt::ServerConnection::AcceptClient()
{
    int clientSockfd;
    if((clientSockfd = accept(sockfd, (sockaddr*)address->GetSockaddrRef(), (socklen_t*)address->GetSocketAddressLengthRef())) < 0)
        throw "Accepting Client Failed";

    return new ConnectionInstance(clientSockfd);
}

void snt::ServerConnection::StartServer(int backlog)
{
    InitialiseSocket();
    BindSocket();
    ListenOnSocket(backlog);
}