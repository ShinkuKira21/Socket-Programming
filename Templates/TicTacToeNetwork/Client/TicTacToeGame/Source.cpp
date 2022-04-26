#include "INet4Address.h"
#include "ClientConnection.h"
#include "ConnectionInstance.h"
#include "Messages.h"
#include "TicTacToeNetworkClient.h"

#include <thread>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace tttmessages;
using namespace std;

int main(int argc, char** argv)
{
	char ip[] = "127.0.0.1";
	INet4Address* address = new INet4Address(ip, 50018);
	ClientConnection* conn = new ClientConnection(address);

	ConnectionInstance* ci = conn->ConnectToServer();

	TicTacToeNetworkClient *nc = new TicTacToeNetworkClient(ci);
	nc->StartGame();

	system("pause");
}