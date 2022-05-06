//
// Created by skira21 on 5/5/22.
//

#include "messages.h"

smt::GameStateMessage::GameStateMessage() {
    state = action;
}

smt::GameStateMessage::GameStateMessage(smt::EGameState gameState)
{
    this->state = action;
    this->gameState = gameState;
}

smt::GameStateMessage::~GameStateMessage()
{ }

void smt::GameStateMessage::Serialise(std::ostream& os)
{
    smt::StateHandler::Serialise(os);
    os << state;
}

void smt::GameStateMessage::UnserialiseType(std::istream& is)
{
    int tmp;
    if (is >> tmp)
        gameState = static_cast<smt::EGameState>(tmp);
}

void smt::GameStateMessage::SetState(smt::EGameState gameState)
{ this->gameState = gameState; }

smt::EGameState smt::GameStateMessage::GetState()
{ return gameState; }