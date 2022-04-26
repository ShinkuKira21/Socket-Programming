#include "GridUpdate.h"

namespace tttmessages
{

	GridUpdate::GridUpdate()
	{
		type = gamegrid;
	}

	GridUpdate::GridUpdate(vector<vector<SquareState>> board)
	{
		type = gamegrid;
		this->board = board;
	}

	GridUpdate::~GridUpdate()
	{
	}

	void GridUpdate::Serialise(ostream& os)
	{
		Message::Serialise(os);

		for (auto i = board.rbegin(); i != board.rend(); i++)
		{
			for (auto j = i->rbegin();j != i->rend();j++)
			{
				os << *j << endl;
			}
		}
	}

	void GridUpdate::UnserialiseType(istream& is)
	{
		//This is potentially risky - we're currently assuming that the client is going to be honest and always send 9.

		for (int i = 0; i < 3; i++)
		{
			vector<SquareState> row;
			for (int j = 0; j < 3; j++)
			{
				int tmp;

				if (is >> tmp)
				{
					row.push_back(static_cast<SquareState>(tmp));
				}
			}

			board.push_back(row);
		}
	}

	vector<vector<SquareState>> GridUpdate::GetBoard()
	{
		return board;
	}

	void GridUpdate::SetBoard(vector<vector<SquareState>> board)
	{
		this->board = board;
	}

}