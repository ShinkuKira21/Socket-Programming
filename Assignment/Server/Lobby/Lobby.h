#pragma once
#include "../Game/RPSNetwork.h"

namespace RPS 
{
    class Lobby 
    {
        private:
            RPS::RPSNetwork* network;

        public:
            static Lobby& Instance();
            ~Lobby();

            RPS::RPSNetwork* GetGame();

        private:
            Lobby();
    };
}