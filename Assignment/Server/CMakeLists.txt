cmake_minimum_req/home/edwardpatch1/Projects/University Wales Trinity St Davids/Socket-Programming/Assignment/Serveruired(VERSION 3.22)
project(Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(../Libraries)
include_directories(Game)
include_directories(Lobby)
include_directories(MessageTools)
include_directories(MessageTools/Messages)
include_directories(NetworkTools)

add_executable(Server
    ../Libraries/INet4Address.cpp
    Game/ConnectedPlayer.cpp
    Game/GameLogic.cpp
    Game/RPSNetwork.cpp
    Lobby/Lobby.cpp
    MessageTools/Messages/AcceptMessage.cpp
    MessageTools/Messages/ActionMessage.cpp
    MessageTools/Messages/ConnectMessage.cpp
    MessageTools/Messages/DisconnectMessage.cpp
    MessageTools/Messages/RefuseMessage.cpp
    MessageTools/Messages/UpdateMessage.cpp
    MessageTools/StateHandler.cpp
    NetworkTools/Connection.cpp
    NetworkTools/ConnectionInstance.cpp
    NetworkTools/ServerConnection.cpp
    main.cpp)
