//
// Created by edwardpatch1 on 4/30/22.
//
#include "cnt.h"

#include <unistd.h>

cnt::ConnectionInstance::ConnectionInstance(int sockfd)
{ this->sockfd = sockfd; }

cnt::ConnectionInstance::~ConnectionInstance() { }

void cnt::ConnectionInstance::SetSocket(int sock)
{ this->sockfd = sock; }

int cnt::ConnectionInstance::GetSocket()
{ return sockfd; }

void cnt::ConnectionInstance::WriteN(const char* data, int bytesToWrite)
{
    int nleft = bytesToWrite;
    int nwritten;

    while(nleft > 0)
    {
        if((nwritten = send(sockfd, data, nleft, 0)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else throw - 1;
        }

        else
        {
            nleft -= nwritten;
            data += nwritten;
        }
    }

    if(nleft != 0) throw nleft;
}

void cnt::ConnectionInstance::ReadN(char* data, int bytesToRead)
{
    int nleft = bytesToRead;
    int nread;

    while (nleft > 0)
    {
        if((nread = recv(sockfd, data, nleft, 0)) < 0)
        {
            if(errno == EINTR) nread = 0;
            else throw -1;
        }
        else
        {
            if(nread == 0) break;
            else{
                nleft -= nread;
                data += nread;
            }
        }
    }
}

void cnt::ConnectionInstance::SendInt(int value)
{
    value = htonl(value);
    char* toSend = (char*)&value;
    WriteN(toSend, int(sizeof(value)));
}

void cnt::ConnectionInstance::SendString(const char* str)
{
    SendInt(strlen(str));
    WriteN(str, strlen(str));
}

int cnt::ConnectionInstance::RecieveInt()
{
    int value = 0;
    char* recvBuffer = (char*)&value;
    ReadN(recvBuffer, sizeof(int));

    return ntohl(value);
}

std::string cnt::ConnectionInstance::RecieveString()
{
    size_t msgSize = RecieveInt();
    char* msg = new char[msgSize + 1];
    ReadN(msg, msgSize);
    msg[msgSize] = '\0';
    std::string finalMSG(msg);

    delete[] msg;
    return finalMSG;
}

void cnt::ConnectionInstance::Disconnect()
{ close(sockfd); }
