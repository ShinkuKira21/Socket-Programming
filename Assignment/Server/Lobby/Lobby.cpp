#include "Lobby.h"

RPS::Lobby::Lobby()
{ network = new RPS::RPSNetwork(); }

RPS::Lobby::~Lobby() {}

RPS::Lobby& RPS::Lobby::Instance()
{
    static RPS::Lobby instance;
    return instance;
}

RPS::RPSNetwork* RPS::Lobby::GetGame()
{ return network; }