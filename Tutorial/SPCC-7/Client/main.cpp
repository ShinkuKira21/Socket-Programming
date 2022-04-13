#include "../Libraries/INet4Address.h"
#include <unistd.h>


/*
    right click on project, properties, change configuration to All Configuration and All Platforms.

    expand linker, input, edit additional dependencies.
    
    add Ws2_32.lib
    Mswsock.lib
    AdvApi32.lib
*/
// SOCKET if Windows
int WriteN(int sockfd, const char* data, int bytesToWrite)
{
    int nleft = bytesToWrite;
    int nwritten;

    while(nleft > 0)
    {
        if((nwritten = send(sockfd, data, nleft, 0)) <= 0)
        {
            if(nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else return -1;
        }
        else 
        {
            nleft -= nwritten;
            data += nwritten;
        }
    }

    return bytesToWrite - nleft;
}
int ReadN(int sockfd, char* data, int bytesToRead)
{
    int nleft = bytesToRead;
    int nread;

    while (nleft > 0)
    {
        if((nread = recv(sockfd, data, nleft, 0) < 0))
        {
            if(errno == EINTR) nread = 0;
            else return -1;
        }
        else
        {
            if(nread == 0) break;

            nleft -= nread;
            data += nread; 
        }
    }

    return bytesToRead - nleft;
}

int ReadSize(int socket)
{
    int value = 0;
    char* recv_buffer = (char*)&value;

    ReadN(socket, recv_buffer, sizeof(int));

    return (int)ntohl(value);
}

void WriteSize(int socket, int size)
{
    size = (int)htonl(size);
    char* tosend = (char*)&size;
    WriteN(socket, tosend, sizeof(int)); 
}

int main(int argc, char** argv)
{
    char const ip[] = "18.135.100.206";
    INet4Address* serverAddress = new INet4Address(ip, 13);

    // comment out next step if not on windows.
    /*WSDATA wsaData;
    if(int errorCode = WSAStartup(MAKEWORD(2,2), &wsaData) < 0)
    {
        std::cout << "Initialisation failed: " << errorCode << std::endl;
        exit(-1);
    }*/
    // windows uses SOCKET
    int sockfd;
    if((sockfd = socket(serverAddress->GetSockaddrRef()->sin_family, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket failed: " << sockfd << std::endl;
        exit(-1);
    }

    int errorCode;
    if((errorCode = connect(sockfd, (sockaddr*)serverAddress->GetSockaddrRef(), (int)serverAddress->GetSocketAddressLengthVal())) < 0)
    {
        std::cout << "Bind failed: " << errorCode << std::endl;
        perror("Err");
        exit(-1);
    }

    int incMessageSize = ReadSize(sockfd);
    std::cout << incMessageSize << std::endl;
    char* incMessage = new char[incMessageSize + 1];

    ReadN(sockfd, incMessage, incMessageSize);
    incMessage[incMessageSize] = '\0';

    std::cout << "incMessage: " << incMessage << std::endl;

    delete serverAddress;
    delete[] incMessage;

    close(sockfd);
}
