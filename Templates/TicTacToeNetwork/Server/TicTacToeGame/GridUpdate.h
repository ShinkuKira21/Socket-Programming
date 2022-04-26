#pragma once

#include <vector>
#include "TicTacToe.h"

#include "Message.h"

namespace tttmessages
{

	class GridUpdate :
		public Message
	{
	public:
		GridUpdate();
		GridUpdate(vector<vector<SquareState>> board);
		~GridUpdate();

		void Serialise(ostream& os) override;
		void UnserialiseType(istream& is) override;

		vector<vector<SquareState>> GetBoard();
		void SetBoard(vector<vector<SquareState>> board);

	private:
		vector<vector<SquareState>> board;
	};

}