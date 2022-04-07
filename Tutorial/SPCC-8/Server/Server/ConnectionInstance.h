#pragma once

#include <string>

using namespace std;

class ConnectionInstance
{
public:
	ConnectionInstance(int sock);
	~ConnectionInstance();

	void Writen(const char *data, int bytesToWrite);
	void Readn(char *data, int bytesToRead);

	void SendInt(int value);
	int ReceiveInt();

	void SendString(string value);
	string ReceiveString();

	void SetSocket(int sock);
	int GetSocket();

private:
	int sock;
};

