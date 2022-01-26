#include <iostream>
#include <string>
#include <sstream>
#include "Directions.h"

std::string StrInput(const char* msg)
{
	std::string input;
	std::cout << msg;
	std::getline(std::cin, input);
	return input;
}

int NumberInput(const char* msg)
{
	std::string input;
	std::stringstream sstream;

	int x = 0;

	std::cout << msg;
	std::getline(std::cin, input);

	sstream.str(input);
	sstream >> x;
	sstream.clear();

	return x;
}
/*
 ^ means move one house North.

> means move one house East.

v means move one house South.

< means move one house West.

 */

bool ValidMove(std::string lastMoves, char latestMove)
{
	if (lastMoves[0] == latestMove)
		return false;

	return true;
}

int main()
{
	Directions dir; std::string lastMove = "";
	// i is latest move, j is last move
	int count = 0;
	for(int i = 0, j = -1; i < dir.directions.length(); i++, j++)
	{
		
		if(j - 1 > -1)
		{
			lastMove += dir.directions[j - 1]; lastMove += dir.directions[j];
			if (ValidMove(lastMove, dir.directions[i]))
				count++;
		}

		lastMove = "";
	}

	std::cout << "Houses Visited: " << count << " | Characters Available: " << dir.directions.length();
	
	return 0;
}