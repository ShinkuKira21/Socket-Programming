#pragma once
#include "../../Libraries/INet4Address.h"

// server network tools
namespace snt 
{
    class Connection 
    {
        protected:
            INet4Address* address;
            int sockfd;

        public:
            Connection(INet4Address* address);
            ~Connection();

            void InitialiseSocket();
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

    class ServerConnection : public Connection {
        public:
            ServerConnection(INet4Address* address);
            ~ServerConnection();

            void BindSocket();
            void ListenOnSocket(int backlog);

            ConnectionInstance* AcceptClient();
            void StartServer(int backlog);
    };
}