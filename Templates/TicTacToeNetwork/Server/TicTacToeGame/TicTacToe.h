#pragma once

class ConnectedPlayer;

#include <vector>
#include <algorithm>

enum SquareState { empty, player1, player2 };

using namespace std;

class TicTacToe
{
public:
	TicTacToe(ConnectedPlayer* p1, ConnectedPlayer* p2);
	~TicTacToe();

	vector<vector<SquareState>> GetBoard();
	bool MakeMove(int column, int row);
	ConnectedPlayer* CheckForVictory();
	bool CheckForMovesRemaining();
	ConnectedPlayer* GetCurrentPlayer();
	void SwapTurn();

private:
	vector<vector<SquareState>> board;
	ConnectedPlayer* p1;
	ConnectedPlayer* p2;

	SquareState playerTurn;

	ConnectedPlayer* GetPlayer(SquareState ss);
};

