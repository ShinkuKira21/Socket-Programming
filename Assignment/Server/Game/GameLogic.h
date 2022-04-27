#pragma once
#include <string>

class ConnectedPlayer;

namespace RPS {
    class RPSGameLogic {
        private:
            ConnectedPlayer* players[2];
            std::string actions[2];
            int turns = 0;

        public:
            RPSGameLogic(ConnectedPlayer* players[2]);
            ~RPSGameLogic();

            void Action(ConnectedPlayer* player, const char* action);
            bool CheckForMovesRemaining();
            ConnectedPlayer* CheckForVictory();
    };
}