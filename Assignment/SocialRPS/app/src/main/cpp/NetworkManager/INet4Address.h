//
// Created by edwardpatch1 on 4/11/22.
//
#ifndef SOCIALRPS_INET4ADDRESS_H
#define SOCIALRPS_INET4ADDRESS_H

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

namespace NetworkManager {
    class INet4Address {
        public:
            INet4Address();
            INet4Address(char* const add, int port);
            INet4Address(int port);

            ~INet4Address();

            //To get a sockaddr_in pointer to pass sto connect
            sockaddr_in* GetSockaddrRef();

            //The two types of length, used depending on how we need to pass them
            size_t* GetSocketAddressLengthRef();
            size_t GetSocketAddressLengthVal();

            //We may want to print the address and port
            //pass in string length so we don't overfill the buffer
            void GetSocketAddress(char* const, int len);
            std::string GetSocketAddress();

            int GetPort();

            //Debugging function
            void Print();

        private:
            sockaddr_in address; //Address structure
            size_t length; //Object size
    };
}

#endif //SOCIALRPS_INET4ADDRESS_H
