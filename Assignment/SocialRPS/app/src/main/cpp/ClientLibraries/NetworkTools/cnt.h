//
// Created by edwardpatch1 on 4/30/22.
//

#ifndef SOCIALRPS_CNT_H
#define SOCIALRPS_CNT_H

#pragma once
#include "../../NetworkManager/INet4Address.h"

// client network tools
namespace cnt
{
    class Connection
    {
        protected:
            NetworkManager::INet4Address* address;
            int sockfd;

        public:
            Connection(NetworkManager::INet4Address* address);
            virtual ~Connection();

            bool InitialiseSocket();
    };

    class ConnectionInstance
    {
        private:
            int sockfd;

        public:
            ConnectionInstance(int sockfd);
            ~ConnectionInstance();

            void SetSocket(int sock);
            int GetSocket();

            void WriteN(const char* data, size_t bytesToWrite);
            void ReadN(char* data, size_t bytesToRead);

            // Senders
            void SendInt(int value);
            void SendString(const char* str);

            // Receivers
            int RecieveInt();
            std::string RecieveString();

            // Disconnection
            void Disconnect();
    };

    class ClientConnection : public Connection
            {
        public:
            ClientConnection(NetworkManager::INet4Address* address);
            ~ClientConnection();

            int BindConnection();
            ConnectionInstance* ConnectToServer();
    };
}

#endif //SOCIALRPS_CNT_H
