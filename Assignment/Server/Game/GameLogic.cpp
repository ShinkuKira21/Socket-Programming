#include "GameLogic.h"

RPS::RPSGameLogic::RPSGameLogic(ConnectedPlayer* players[2])
{ 
    for(size_t i = 0; i < 2; i++)
        this->players[i] = players[i];
}

RPS::RPSGameLogic::~RPSGameLogic() { }

void RPS::RPSGameLogic::Action(ConnectedPlayer* player, const char* action)
{
    if(players[0] == player)
        this->actions[0] = action;
    else this->actions[1] = action;
}

bool RPS::RPSGameLogic::CheckForMovesRemaining()
{ return false; }