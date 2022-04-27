#include "../Libraries/INet4Address.h"

#include "NetworkTools/snt.h"
#include "Game/RPSNetwork.h"
#include "MessageTools/Messages/messages.h"
#include "Lobby/Lobby.h"

#include <thread>

void ClientHandler(snt::ConnectionInstance* ci)
{
    smt::StateHandler* stateHandler;
    RPS::ConnectedPlayer* player;

    while(true)
    {
        std::string msg = ci->RecieveString();
        stateHandler = smt::StateHandler::Unserialise(msg.c_str());

        if(stateHandler->GetState() == smt::connect)
        {
            
            player = new RPS::ConnectedPlayer(((smt::ConnectMessage*)stateHandler)->GetUsername().c_str(), ci);

            // The Java (Client) Application takes care of the username requirements - However, just make sure that the username is not blank.
            if(player->GetPlayerName().empty())
            {
                // Blank Message
                smt::StateHandler* reply = new smt::RefuseMessage("Error10");
                ci->SendString(reply->Serialise().c_str());

                delete reply;
                delete player;
            }

            else if(!RPS::Lobby::Instance().GetGame())
            {
                // Lobby Full
                smt::StateHandler* reply = new smt::RefuseMessage("Err20");
                ci->SendString(reply->Serialise().c_str());

                delete reply;
                delete player;
            }

            else 
            {
                // Success
                smt::StateHandler* reply = new smt::AcceptMessage("Accepted");
                ci->SendString(reply->Serialise().c_str());

                delete reply;
                break;
            }
        }
        else
        {
            smt::StateHandler* reply = new smt::AcceptMessage("Accepted");
            ci->SendString(reply->Serialise().c_str());

            delete reply;
            break;
        }
    }

    // Starts the Game!
    RPS::Lobby::Instance().GetGame()->PlayGame(player);
}

int main(int argc, char** argv)
{
    INet4Address* address = new INet4Address(50018);
    snt::ServerConnection* server = new snt::ServerConnection(address);

    server->StartServer(100);

    while(true)
    {
        snt::ConnectionInstance* ci = server->AcceptClient();
        std::thread(ClientHandler, ci).detach();
    }

    system("PAUSE");
}