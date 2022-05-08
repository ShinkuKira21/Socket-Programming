//
// Created by edwardpatch1 on 4/11/22.
//
#include <thread>
#include "GameActivity.h"
#include "../ClientLibraries/MessageTools/Messages/messages.h"

GameActivity::GameActivity::GameActivity(cnt::ConnectionInstance* cInstance, ClientStructure clientInfo)
{
    this->cInstance = cInstance;
    this->clientInfo = clientInfo;
}

GameActivity::GameActivity::~GameActivity() { delete cInstance; }

bool GameActivity::GameActivity::RegisterGame() {
    while(true)
    {
        smt::ConnectMessage* connectMessage = new smt::ConnectMessage();
        connectMessage->SetUsername(clientInfo.playerName);

        SendNetworkMessage(connectMessage);
        delete connectMessage;
        smt::StateHandler* state = GetNetworkMessage();

        if(state == nullptr) return false;
        switch (state->GetState())
        {
            case smt::accept:
                delete state;
                return true;

            default:
                delete state;
                return false;
        }
    }
}

void GameActivity::GameActivity::SendNetworkMessage(smt::StateHandler* state) {
    try {
        cInstance->SendString(state->Serialise().c_str());
    } catch (...)
    {
        throw -1;
    }
}

smt::StateHandler* GameActivity::GameActivity::GetNetworkMessage() {
    try {
        std::string msg = cInstance->RecieveString();
        return smt::StateHandler::Unserialise(msg.c_str());
    } catch (...)
    {
        return nullptr;
    }
}

bool GameActivity::GameActivity::RequestUpdate() {
    smt::UpdateMessage* updateMessage = new smt::UpdateMessage();
    SendNetworkMessage(updateMessage);
    delete updateMessage;
    smt::StateHandler* state = GetNetworkMessage();

    if(state->GetState() == smt::action)
    {
        if(((smt::GamePhaseMessage*)state)->GetState() == smt::EGamePhase::playing) return true;

        return false;
    }

    // could be ideal for some proper handling here
    throw -1;
}

std::string GameActivity::GameActivity::MakeMove() {
    return std::string();
}