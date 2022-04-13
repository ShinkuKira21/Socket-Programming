//
// Created by edwardpatch1 on 4/11/22.
//

#ifndef SOCIALRPS_GAMEACTIVITY_H
#define SOCIALRPS_GAMEACTIVITY_H

#include <iostream>

namespace GameActivity {
    struct ClientStructure {
        const char* playerName;
        int action;
    };

    class GameActivity {
        ClientStructure clientInfo;

        public:
            GameActivity(ClientStructure clientInfo);
    };
}

#endif //SOCIALRPS_GAMEACTIVITY_H
