//
// Created by edwardpatch1 on 4/12/22.
//

namespace cnt {
    inline int WriteN(int sockfd, const char* data, int bytesToWrite)
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

    inline int ReadN(int sockfd, char* data, int bytesToRead)
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

    void WriteSize(int socket, int size) {
        size = (int) ntohl(size);
        char *tosend = (char*) &size;
        WriteN(socket, tosend, sizeof(int));
    }
}

