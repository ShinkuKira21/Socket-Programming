#pragma once

#include <vector>
enum SquareState { empty, player1, player2 };

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