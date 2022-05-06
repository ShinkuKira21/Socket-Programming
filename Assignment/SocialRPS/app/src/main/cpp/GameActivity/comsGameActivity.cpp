//
// Created by skira21 on 5/5/22.
//

#include <jni.h>
#include "GameActivity.h"
#include "../NetworkManager/INet4Address.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_uwtsd_socialrps_GameActivity_InitiateConnectionInstance(JNIEnv *env, jobject thiz, jstring ip, int port, jstring username) {
    // TODO: implement PostAction()
    const char* cIP = env->GetStringUTFChars(ip, NULL);

    char* finalIP = new char[env->GetStringUTFLength(ip)];
    strcpy(finalIP, cIP);

    NetworkManager::INet4Address address(finalIP, port);
    delete[] finalIP;

    cnt::ClientConnection* serverConnection = new cnt::ClientConnection(&address);

    cnt::ConnectionInstance* cInstance = serverConnection->ConnectToServer();

    delete serverConnection;
    return (jlong)cInstance;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_uwtsd_socialrps_GameActivity_DeconstructConnectionInstance(JNIEnv *env, jobject thiz,
                                                                    jlong c_instance) {
    // TODO: implement DeconstructConnectionInstance()
    cnt::ConnectionInstance* cInstance = (cnt::ConnectionInstance*) cInstance;
    delete cInstance;
}