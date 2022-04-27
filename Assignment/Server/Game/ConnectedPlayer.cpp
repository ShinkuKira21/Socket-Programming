#include "RPSNetwork.h"

RPS::ConnectedPlayer::ConnectedPlayer(const char* playerName, snt::ConnectionInstance* ci)
{
    this->playerName = playerName;
    this->ci = ci;
    this->status = connected;
}

RPS::ConnectedPlayer::~ConnectedPlayer()
{ }

void RPS::ConnectedPlayer::SetPlayerName(const char* playerName)
{ this->playerName = playerName; }

std::string RPS::ConnectedPlayer::GetPlayerName()
{ return playerName; }

void RPS::ConnectedPlayer::SetConnectionInstance(snt::ConnectionInstance* ci)
{ this->ci = ci; }

snt::ConnectionInstance* RPS::ConnectedPlayer::GetConnectionInstance()
{ return ci; }

smt::StateHandler* RPS::ConnectedPlayer::GetNetworkState()
{ 
    try 
    {
        std::string msgString = ci->RecieveString();
        smt::StateHandler* state = smt::StateHandler::Unserialise(msgString.c_str());

        if(state->GetState() == smt::disconnect)
        {
            std::cout << "Information: " << playerName << " disconnected during game." << std::endl;
            SetDisconnected();
        }
        
        return state;
    }
    catch (...)
    {
        std::cout << "Information: " << playerName << " disconnected unexpectedly." << std::endl;
        SetDisconnected();
        return nullptr;
    }
}

void RPS::ConnectedPlayer::SendNetworkState(smt::StateHandler* state)
{
    try
    {
        ci->SendString(state->Serialise().c_str());
    }

    catch (...)
    {
        std::cout << "Information: " << playerName << " disconnected unexpectedly." << std::endl;
        SetDisconnected();
    }
}

PlayerConnectionStatus RPS::ConnectedPlayer::GetConnectionStatus()
{ return status; }

void RPS::ConnectedPlayer::SetDisconnected()
{ status = disconnected; }