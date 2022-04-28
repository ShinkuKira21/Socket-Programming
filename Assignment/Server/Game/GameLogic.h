#pragma once

#include <string>

namespace RPS {
    class ConnectedPlayer;
    class RPSGameLogic {
        private:
            ConnectedPlayer** players;
            std::string actions[2];
            int turns = 0;

        public:
            RPSGameLogic(ConnectedPlayer** players);
            ~RPSGameLogic();

            void Action(ConnectedPlayer* player, const char* action);
            bool CheckForMovesRemaining();
            ConnectedPlayer* CheckForVictory();
    };
}