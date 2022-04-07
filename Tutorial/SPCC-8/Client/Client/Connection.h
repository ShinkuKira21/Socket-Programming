#pragma once

#include "../../Libraries/INet4Address.h"
#include "ConnectionInstance.h"

class Connection
{
public:
	Connection(INet4Address* address);
	~Connection();

	void InitialiseSocket();
	void CreateSocket();

protected:
	INet4Address *address;
	int sockfd;

};

