//
// Created by edwardpatch1 on 4/11/22.
//

#ifndef SOCIALRPS_GAMEACTIVITY_H
#define SOCIALRPS_GAMEACTIVITY_H

#include "../ClientLibraries/NetworkTools/cnt.h"
#include "../ClientLibraries/MessageTools/smt.h"

namespace GameActivity {
    struct ClientStructure {
        const char* playerName;
    };

    class GameActivity {
            ClientStructure clientInfo;
            cnt::ConnectionInstance* cInstance;

            public:
                GameActivity(cnt::ConnectionInstance* cInstance, ClientStructure clientInfo);
                ~GameActivity();

                bool RegisterGame();
                bool RequestUpdate();

                std::string MakeMove();

            private:
                void SendNetworkMessage(smt::StateHandler* state);
                smt::StateHandler* GetNetworkMessage();
        };
}

#endif //SOCIALRPS_GAMEACTIVITY_H
