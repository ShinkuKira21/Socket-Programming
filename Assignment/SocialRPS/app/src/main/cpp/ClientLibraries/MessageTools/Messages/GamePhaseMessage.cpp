//
// Created by skira21 on 5/8/22.
//

//
// Created by skira21 on 5/7/22.
//

#include "messages.h"

smt::GamePhaseMessage::GamePhaseMessage()
{ state = action; }

smt::GamePhaseMessage::GamePhaseMessage(EGamePhase phase)
{
    state = action;
    this->phase = phase;
}

smt::GamePhaseMessage::~GamePhaseMessage()
{ }

void smt::GamePhaseMessage::Serialise(std::ostream &os) {
    smt::StateHandler::Serialise(os);
    os << phase;
}

void smt::GamePhaseMessage::UnserialiseState(std::istream &is) {
    int tmp;
    if(is >> tmp)
        phase = static_cast<EGamePhase>(tmp);
}

void smt::GamePhaseMessage::SetState(EGamePhase phase) {
    this->phase = phase;
}

smt::EGamePhase smt::GamePhaseMessage::GetState() {
    return phase;
}