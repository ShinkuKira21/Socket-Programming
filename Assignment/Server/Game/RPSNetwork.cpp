#include "RPSNetwork.h"
#include "../MessageTools/Messages/messages.h"

RPS::RPSNetwork::RPSNetwork() {
    state = smt::waiting;
}

RPS::RPSNetwork::~RPSNetwork() 
{ delete rps; }

void RPS::RPSNetwork::PlayGame(ConnectedPlayer* tPlayer)
{
    ConnectedPlayer* winner = nullptr, *opponent;

    while(players[0] == nullptr || players[1] == nullptr)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    if(tPlayer == players[0]) opponent = players[1];
    else if(tPlayer == players[1]) opponent = players[0];

    else 
    {
        std::cerr << "A player disconnected..." << std::endl;
        return;
    }

    while(winner == nullptr && rps->CheckForMovesRemaining())
    {
        while(true)
        {
            smt::StateHandler* state = tPlayer->GetNetworkState();

            if(state == nullptr || state->GetState() == smt::disconnect)
            {
                tPlayer->SetDisconnected();
                return;
            }

                // Invalid Message
            else if(state->GetState() != smt::update)
                tPlayer->SendNetworkState(new smt::RefuseMessage("Err30"));

            else
            {
                if(tPlayer->GetConnectionStatus() == connected && opponent->GetConnectionStatus() == disconnected)
                {
                    tPlayer->SetDisconnected();
                    tPlayer->SendNetworkState(new smt::DisconnectMessage("Err31"));
                    return;
                }

                if(tPlayer->GetConnectionStatus() == connected && opponent->GetConnectionStatus() == disconnected)
                {
                    tPlayer->SetDisconnected();
                    tPlayer->SendNetworkState(new smt::DisconnectMessage("Err32"));
                    return;
                }

                // return final state (should be playing)
                tPlayer->SendNetworkState(new smt::GamePhaseMessage(this->state));

                break;
            }
        }

        // displays the end game state
        bool bVictory = false;
        while(!bVictory)
        {
            smt::StateHandler* state = tPlayer->GetNetworkState();

            if(state->GetState() == smt::action)
            {
                rps->Action(tPlayer, ((smt::ActionMessage*)state)->GetMessage().c_str());
            }
        }
    }
}

smt::EGamePhase RPS::RPSNetwork::GetState()
{ return state; }

bool RPS::RPSNetwork::AddPlayer(ConnectedPlayer* player)
{
    if(players[0] == nullptr)
    {
        players[0] = player;
        return true;
    }
    
    if(players[1] == nullptr)
    {
        players[1] = player;
        InitialiseGame();
        return true;
    }
    
    return false;
}

void RPS::RPSNetwork::InitialiseGame()
{
    rps = new RPS::RPSGameLogic(players);
    state = smt::EGamePhase::playing;
}