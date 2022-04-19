//
// Created by edwardpatch1 on 4/11/22.
//

#include "INet4Address.h"
#include "NetworkTools.h"
#include <thread>
#include <unistd.h>
#include <ostream>
#include <sstream>
#include <jni.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_uwtsd_socialrps_GameManager_NetworkTest(JNIEnv *env, jobject thiz) {
    // TODO: implement NetworkTest()
    {
        std::stringstream stream;
        std::string result;

        char ip[] = "3.11.23.103";
        NetworkManager::INet4Address* serverAddress = new NetworkManager::INet4Address(ip, 13);
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
            stream << "Socket failed: " << sockfd << std::endl;
            result = stream.str();
            perror("Err");
            delete serverAddress;
            return env->NewStringUTF(result.c_str());
        }

        int errorCode;
        if((errorCode = connect(sockfd, (sockaddr*)serverAddress->GetSockaddrRef(), (int)serverAddress->GetSocketAddressLengthVal())) < 0)
        {
            perror("Err");
            stream << "Bind failed: " << errorCode << std::endl;
            result = stream.str();

            delete serverAddress;
            return env->NewStringUTF(result.c_str());
        }

        int incMessageSize = cnt::ReadSize(sockfd);
        char* incMessage = new char[incMessageSize + 1];

        cnt::ReadN(sockfd, incMessage, incMessageSize);
        incMessage[incMessageSize] = '\0';

        stream << "incMessage: " << incMessage << "Here" << std::endl;
        result = stream.str();

        delete serverAddress;
        delete[] incMessage;

        close(sockfd);

        return env->NewStringUTF(result.c_str());
    }
}