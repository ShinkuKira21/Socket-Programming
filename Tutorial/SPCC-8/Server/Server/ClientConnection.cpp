#include "ClientConnection.h"



ClientConnection::ClientConnection(INet4Address* address) : Connection(address)
{
}


ClientConnection::~ClientConnection()
{
}

void ClientConnection::BindConnection()
{
	if (int errorCode = connect(sockfd, (sockaddr*)address->GetSockaddrRef(), (int)address->GetSocketAddressLengthVal()) < 0)
	{
		throw "Error binding";
	}
}

ConnectionInstance* ClientConnection::ConnectToServer()
{
	InitialiseSocket();
	CreateSocket();
	BindConnection();

	return new ConnectionInstance(sockfd);
}