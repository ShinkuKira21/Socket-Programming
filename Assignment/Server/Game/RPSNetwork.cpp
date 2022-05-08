#include "RPSNetwork.h"
#include "../MessageTools/Messages/messages.h"

RPS::RPSNetwork::RPSNetwork() {
    state = smt::waiting;
}

RPS::RPSNetwork::~RPSNetwork() 
{ }

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
            {
                smt::RefuseMessage* refuseMessage = new smt::RefuseMessage("Err30");
                tPlayer->SendNetworkState(refuseMessage);
                delete refuseMessage;
            }

            else
            {
                if(tPlayer->GetConnectionStatus() == connected && opponent->GetConnectionStatus() == disconnected)
                {
                    tPlayer->SetDisconnected();
                    smt::RefuseMessage* refuseMessage = new smt::RefuseMessage("Err31");
                    tPlayer->SendNetworkState(refuseMessage);
                    delete refuseMessage;
                    return;
                }

                if(tPlayer->GetConnectionStatus() == connected && opponent->GetConnectionStatus() == disconnected)
                {
                    tPlayer->SetDisconnected();
                    smt::RefuseMessage* refuseMessage = new smt::RefuseMessage("Err32");
                    tPlayer->SendNetworkState(refuseMessage);
                    delete refuseMessage;
                    return;
                }

                // return final state (should be playing)
                smt::GamePhaseMessage* gamePhaseMessage = new smt::GamePhaseMessage(GetState());
                tPlayer->SendNetworkState(gamePhaseMessage);
                delete gamePhaseMessage;
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

    // change the players array to p1 and p2...
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
    rps = new RPS::RPSGameLogic(players[0], players[1]);
    state = smt::EGamePhase::playing;
}