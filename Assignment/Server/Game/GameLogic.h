#pragma once

#include <string>
#include <vector>

namespace RPS {
    class ConnectedPlayer;
    class RPSGameLogic {
        private:
            ConnectedPlayer** players;
            std::string actions[2];
            // wins = { 0 = p1, 1 = p2, 2 = draw }
            std::vector<int> wins;
            int turns = 3;

        public:
            RPSGameLogic(ConnectedPlayer** players);
            ~RPSGameLogic();

            void Action(ConnectedPlayer* player, const char* action);
            size_t CheckForMovesRemaining();

            bool CheckForVictory();
            ConnectedPlayer* GetVictory();
    };
}