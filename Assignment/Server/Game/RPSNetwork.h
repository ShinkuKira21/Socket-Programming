#pragma once
#include "../NetworkTools/snt.h"
#include "../MessageTools/smt.h"
#include "GameLogic.h"
#include <thread>

enum GamePhase {
        Playing,
        Finished
    };

enum PlayerConnectionStatus {connected, disconnected};

namespace RPS 
{   
    class ConnectedPlayer 
    {
        private:
            std::string playerName;
            snt::ConnectionInstance* ci;
            PlayerConnectionStatus status;

        public:
            ConnectedPlayer(const char* playerName, snt::ConnectionInstance* ci);
            ~ConnectedPlayer();

            void SetPlayerName(const char* playerName);
            std::string GetPlayerName();

            void SetConnectionInstance(snt::ConnectionInstance* ci);
            snt::ConnectionInstance* GetConnectionInstance();

            smt::StateHandler* GetNetworkState();
            void SendNetworkState(smt::StateHandler* state);

            PlayerConnectionStatus GetConnectionStatus();
            void SetDisconnected();
    };

    class RPSNetwork 
    {
        private:
            RPS::RPSGameLogic* rps;
            ConnectedPlayer* players[2];

            GamePhase state;

        public:
            RPSNetwork();
            ~RPSNetwork();

            void PlayGame(ConnectedPlayer* tPlayer);

            GamePhase GetState();
            bool AddPlayer(ConnectedPlayer* player);

        private:
            void HandleDisconnect(ConnectedPlayer* opponent);
            void InitialiseGame();
    };
}