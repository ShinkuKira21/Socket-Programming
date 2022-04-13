#include "../Libraries/INet4Address.h"
#include <thread>
#include <unistd.h>

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

    return (int)htonl(value);
}

void WriteSize(int socket, int size)
{
    size = (int)ntohl(size);
    char* tosend = (char*)&size;
    WriteN(socket, tosend, sizeof(int)); 
}

int main(int argc, char** argv)
{
    INet4Address serverAddress(13);
     // comment out next step if not on windows.
    /*WSDATA wsaData;
    if(int errorCode = WSAStartup(MAKEWORD(2,2), &wsaData) < 0)
    {
        std::cout << "Initialisation failed: " << errorCode << std::endl;
        exit(-1);
    }*/
    // windows uses SOCKET

    int sockfd;
    if((sockfd = socket(serverAddress.GetSockaddrRef()->sin_family, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Socket failed: " << sockfd << std::endl;
        exit(-1);
    }
    
    if(int errorCode = bind(sockfd, (sockaddr*)serverAddress.GetSockaddrRef(), serverAddress.GetSocketAddressLengthVal()) < 0)
    {
        std::cout << "Bind failed: " << errorCode << std::endl;
        perror("Err");
        exit(-1);
    }

    if(listen(sockfd, 100) < 0)
    {
        std::cout << "Listen failed: " << sockfd << std::endl;
        exit(-1);
    }


    while(true)
    {
        int clientSock;
        if((clientSock = accept(sockfd, (sockaddr*)serverAddress.GetSockaddrRef(), (socklen_t*)serverAddress.GetSocketAddressLengthRef())) < 0)
        {
            std::cout << "Accept Error." << std::endl;
            exit(-1);
        }

        else {
            char buff[256];
            serverAddress.GetSocketAddress(buff, sizeof(buff));
    
            std::cout << "Got connection from " << buff << ':' << serverAddress.GetPort() << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(10));

            std::thread* t = new std::thread([clientSock, sockfd] {
                // Do stuff
                std::string sendString = "Hello World";
                WriteSize(clientSock, sendString.length());
                WriteN(sockfd, sendString.c_str(), sendString.length());
            });

            t->join();  
            delete t;
            break;
        }
    }

    close(sockfd);
}