#include "snt.h"

snt::ConnectionInstance::ConnectionInstance(int sockfd)
{
    this->sockfd = sockfd;
}

snt::ConnectionInstance::~ConnectionInstance() {}

void snt::ConnectionInstance::SetSocket(int sock)
{
    this->sockfd = sock;
}

int snt::ConnectionInstance::GetSocket()
{
    return sockfd;
}

void snt::ConnectionInstance::WriteN(const char* data, size_t bytesToWrite)
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

void snt::ConnectionInstance::ReadN(char* data, size_t bytesToRead)
{
    int nleft = bytesToRead;
    int nread;

    while (nleft > 0)
    {
        if((nread = recv(sockfd, data, nleft, 0) < 0))
        {
            if(errno == EINTR) nread = 0;
            else throw -1;
        }
        else
        {
            nleft -= nread;
            data += nread;
        }
    }
}

void snt::ConnectionInstance::SendInt(int value)
{
    value = htonl(value);
    char* toSend = (char*)&value;
    WriteN(toSend, int(sizeof(value)));
}

void snt::ConnectionInstance::SendString(const char* str)
{
    SendInt(strlen(str));
    WriteN(str, strlen(str));
}

int snt::ConnectionInstance::RecieveInt()
{
    int value = 0;
    char* recvBuffer = (char*)&value;
    ReadN(recvBuffer, sizeof(int));

    return ntohl(value);
}

std::string snt::ConnectionInstance::RecieveString()
{
    size_t msgSize = RecieveInt();
    char* msg = new char[msgSize + 1];
    ReadN(msg, msgSize);
    msg[msgSize] = '\0';
    std::string finalMSG(msg);

    delete[] msg;
    return finalMSG;
}