#pragma once

#include <string>
#include <sstream>

#include "ConnectionInstance.h"
#include "Messages.h"

using namespace std;
using namespace tttmessages;

class TicTacToeNetworkClient
{
public:
	TicTacToeNetworkClient(ConnectionInstance* ci);
	~TicTacToeNetworkClient();

	string GetStringFromConsole(string prompt);
	int GetIntFromConsole(string prompt);

	void StartGame();

	void SendNetworkMessage(Message* m);
	Message* GetNetworkMessage();

private:
	ConnectionInstance* ci;

	bool ConnectToTTTServer();
	GameState* PlayGame();

	void PrintBoard(vector<vector<SquareState>> board);

	void GetGridUpdate();
	void GetGridUpdate(Message* rg);
};

