#include "GameLogic.h"
#include "RPSNetwork.h"

RPS::RPSGameLogic::RPSGameLogic(RPS::ConnectedPlayer** players)
{ 
    this->players = players;
}

RPS::RPSGameLogic::~RPSGameLogic() { }

void RPS::RPSGameLogic::Action(RPS::ConnectedPlayer* player, const char* action)
{
    if(players[0] == player)
        this->actions[0] = action;
    else this->actions[1] = action;
}

bool RPS::RPSGameLogic::CheckForMovesRemaining()
{ return false; }

RPS::ConnectedPlayer* RPS::RPSGameLogic::CheckForVictory()
{ return nullptr; }