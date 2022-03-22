#include <sstream>
#include <chrono>
#include <iomanip>
#include <thread>

#include "ServerConnection.h"
#include "INet4Address.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace networkshapes;
using namespace std;

void ClientHandler(ConnectionInstance* ci)
{

	//TODO: complete this.
	delete ci;
}


int main(int argc, char** argv)
{

	INet4Address *clientAddress = new INet4Address(50018);

	ServerConnection* conn = new ServerConnection(clientAddress);

	conn->StartServer(100);

	while (true)
	{
		ConnectionInstance* ci = conn->AcceptClient();

		thread(ClientHandler, ci).detach();
	}
}