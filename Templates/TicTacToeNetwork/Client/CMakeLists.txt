cmake_minimum_required(VERSION 3.22)
project(Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(TicTacToeGame)

add_executable(Client
        TicTacToeGame/AcceptMessage.cpp
        TicTacToeGame/AcceptMessage.h
        TicTacToeGame/ClientConnection.cpp
        TicTacToeGame/ClientConnection.h
        TicTacToeGame/Connection.cpp
        TicTacToeGame/Connection.h
        TicTacToeGame/ConnectionInstance.cpp
        TicTacToeGame/ConnectionInstance.h
        TicTacToeGame/ConnectMessage.cpp
        TicTacToeGame/ConnectMessage.h
        TicTacToeGame/DisconnectMessage.cpp
        TicTacToeGame/DisconnectMessage.h
        TicTacToeGame/GameState.cpp
        TicTacToeGame/GameState.h
        TicTacToeGame/GridUpdate.cpp
        TicTacToeGame/GridUpdate.h
        TicTacToeGame/INet4Address.cpp
        TicTacToeGame/INet4Address.h
        TicTacToeGame/MakeMove.cpp
        TicTacToeGame/MakeMove.h
        TicTacToeGame/Message.cpp
        TicTacToeGame/Message.h
        TicTacToeGame/Messages.h
        TicTacToeGame/RejectMessage.cpp
        TicTacToeGame/RejectMessage.h
        TicTacToeGame/RequestUpdate.cpp
        TicTacToeGame/RequestUpdate.h
        TicTacToeGame/ServerConnection.cpp
        TicTacToeGame/ServerConnection.h
        TicTacToeGame/Source.cpp
        TicTacToeGame/TicTacToeNetworkClient.cpp
        TicTacToeGame/TicTacToeNetworkClient.h)
