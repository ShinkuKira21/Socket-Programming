//
// Created by edwardpatch1 on 4/11/22.
//

#include "INet4Address.h"

NetworkManager::INet4Address::INet4Address()
{
}


NetworkManager::INet4Address::INet4Address(char* const add, int port)
{
    //Zero the entire address structure (use memset)
    //Set the sin_family attribute to IPv4 (AF_INET)
    //Set the port - remember host/network byte ordering
    //Set the address - use presentation to network
    //Set the length attribute (use sizeof)

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_pton(AF_INET, add, &address.sin_addr);

    length = sizeof(address);
}

NetworkManager::INet4Address::INet4Address(int port)
{
    //Similar to the above, but set the address (using sinaddr.s_addr) to INADDR_ANY
    //Note: INADDR_ANY is a long, currently in host format.  Remember to convert it!
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    length = sizeof(address);
}


NetworkManager::INet4Address::~INet4Address()
{
    //Nothing here :)
}

sockaddr_in* NetworkManager::INet4Address::GetSockaddrRef()
{
    //Pointer to structure
    return &address;
}

size_t* NetworkManager::INet4Address::GetSocketAddressLengthRef()
{
    //Pointer to length of structure
    return &length;
}

size_t NetworkManager::INet4Address::GetSocketAddressLengthVal()
{
    //Value length of structure
    return length;
}

void NetworkManager::INet4Address::GetSocketAddress(char* cstr, int len)
{
    //Address as a string - note, uses the cstr parameter.
    //This should use the network to presentation call - cstr is the buffer, len is the length
    //Don't overthink this - this function is likely only a single call to inet_ntop
    inet_ntop(AF_INET, &address.sin_addr, cstr, len);
}

std::string NetworkManager::INet4Address::GetSocketAddress()
{
    //Make a character array of the size of the maximum address string length - defined by INET_ADDRSTRLEN
    char cstr[INET_ADDRSTRLEN];

    //Call GetSocketAddress using the array/length
    GetSocketAddress(cstr, INET_ADDRSTRLEN);

    //Convert the character array to a std::string (can be done in the string's constructor) and return it
    return std::string(cstr);
}

int NetworkManager::INet4Address::GetPort()
{
    //Return the port.  Remember, convert to host byte order
    return ntohs(address.sin_port);
}

void NetworkManager::INet4Address::Print()
{
    //For debugging
    //Print (using cout) the address and port in the format:
    //192.168.0.1:1000
    //Remember, you can use the functions you've already written to help
    //Don't forget host byte ordering for the port
    std::cout << GetSocketAddress() << ":" << GetPort() << std::endl;
}