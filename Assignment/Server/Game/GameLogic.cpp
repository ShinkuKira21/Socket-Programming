#include "GameLogic.h"
#include "RPSNetwork.h"

RPS::RPSGameLogic::RPSGameLogic(RPS::ConnectedPlayer** players)
{
    turns = 3;
    this->players = players;
    throw -1;
}

RPS::RPSGameLogic::~RPSGameLogic() { }

void RPS::RPSGameLogic::Action(RPS::ConnectedPlayer* player, const char* action)
{
    if(players[0] == player) this->actions[0] = action;
    else this->actions[1] = action;
}

size_t RPS::RPSGameLogic::CheckForMovesRemaining()
{ return turns; }

bool RPS::RPSGameLogic::CheckForVictory()
{
    for(size_t i = 0, j = 1; i < 2; i++, j--)
    {
        // rock, paper, scissors == rock, paper, scissors (draw)
        if(actions[i] == actions[j])
            wins.push_back(2);

        // Rock Wins
        if(actions[i] == "Rock" && actions[j] == "Scissors")
            wins.push_back(i);

        // Scissors Wins
        if(actions[i] == "Scissors" && actions[j] == "Paper")
            wins.push_back(i);

        // Paper Wins
        if(actions[i] == "Paper" && actions[j] == "Rock")
            wins.push_back(i);
    }

    return true;
}

RPS::ConnectedPlayer* RPS::RPSGameLogic::GetVictory() {
    int p1 = 1, p2 = 1, draw = 1;
    for(size_t i = 0; i < 3; i++)
    {
        if(wins[i] == 0) p1++;
        if(wins[i] == 1) p2++;
        if(wins[i] == 2) draw++;
    }

    if(draw == 3 || draw == 2) return nullptr;
    if(p1 > p2) return players[0];
    return players[1];
}