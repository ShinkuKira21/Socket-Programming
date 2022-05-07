#include "INet4Address.h"
#include "ServerConnection.h"
#include "ConnectionInstance.h"
#include "TicTacToeNetwork.h"
#include "Messages.h"
#include "Lobby.h"

#include <thread>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace tttmessages;
using namespace std;

void ClientHandler(ConnectionInstance* ci)
{
	//When the client first connects, we expect them to send a ConnectMessage object.

	Message* m;
	ConnectedPlayer* player;

	//This is a bit lazy, but then, so am I :)
	while (true)
	{
		string msgStr = ci->ReceiveString();
		m = Message::Unserialise(msgStr);

		if (m->GetType() == MessageType::connect)
		{
			//TODO: consider whether username should be enforced to be unique here.

			player = new ConnectedPlayer(((ConnectMessage*)m)->GetUsername(), ci);
			
			//Check whether the name is long enough.
			if (player->GetPlayerName().length() < 2)
			{
				Message* reply = new RejectMessage("Error: Please pick a longer username to connect (at least 3 letters).");
				ci->SendString(reply->Serialise());
				delete reply;
				delete player;
                break;
			}
			else if (!Lobby::Inst().GetGame()->AddPlayer(player))
			{
				Message* reply = new RejectMessage("Unfortunately the game is full.  I will implement a lobby one day...");
				ci->SendString(reply->Serialise());
				delete reply;
				delete player;
                break;
				//close the connection
			}
			else
			{
				Message* reply = new AcceptMessage("Welcome to the server, " + ((ConnectMessage*)m)->GetUsername() + "!");
				ci->SendString(reply->Serialise());
				delete reply;
				break;
			}
		}
		else
		{
			Message* reply = new RejectMessage("Error: could not read connection data, please try again.");
			ci->SendString(reply->Serialise());
			delete reply;
            break;
		}
	}

	Lobby::Inst().GetGame()->PlayGame(player);
}

int main(int argc, char** argv)
{

	INet4Address* address = new INet4Address(50018);
	ServerConnection* server = new ServerConnection(address);

	server->StartServer(100);

	while (true)
	{
		ConnectionInstance* ci = server->AcceptClient();
		thread(ClientHandler, ci).detach();
	}


	system("pause");
}