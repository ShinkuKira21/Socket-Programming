#include "ServerConnection.h"

ServerConnection::ServerConnection(INet4Address* address) : Connection(address)
{
}


ServerConnection::~ServerConnection()
{

}

void ServerConnection::BindSocket()
{
	if (int errorCode = ::bind(sockfd, (sockaddr *)address->GetSockaddrRef(), (int)address->GetSocketAddressLengthVal()) < 0)
	{
		throw "Binding socket failed";
	}
}

void ServerConnection::ListenOnSocket(int backlog)
{
	if (listen(sockfd, backlog) < 0)
	{
		throw "Listening socket failed";
	}
}

ConnectionInstance* ServerConnection::AcceptClient()
{
	int clientSock;

	if ((clientSock = accept(sockfd, (sockaddr*)address->GetSockaddrRef(), (socklen_t*)address->GetSocketAddressLengthRef())) < 0)
	{
		throw "Accept socket failed";
	}

	return new ConnectionInstance(clientSock);
}

void ServerConnection::StartServer(int backlog)
{
	InitialiseSocket();
	CreateSocket();
	BindSocket();
	ListenOnSocket(backlog);

	
}