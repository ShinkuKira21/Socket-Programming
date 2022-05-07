//
// Created by skira21 on 5/5/22.
//

#include <jni.h>
#include "GameActivity.h"
#include "../NetworkManager/INet4Address.h"
#include "../NetworkManager/Configuration.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_uwtsd_socialrps_GameActivity_InitiateGameActivity(JNIEnv *env, jobject thiz, jstring username) {
    // TODO: implement InitiateGameActivity
    NetworkManager::INet4Address* address = new NetworkManager::INet4Address(NetworkManager::ServerConfiguration::ip, NetworkManager::ServerConfiguration::port);
    cnt::ClientConnection* serverConnection = new cnt::ClientConnection(address);
    cnt::ConnectionInstance* cInstance = serverConnection->ConnectToServer();

    if(cInstance == nullptr)
    {
        delete address;
        delete serverConnection;
        delete cInstance;

        return 0;
    }

    GameActivity::GameActivity* gameActivity = new GameActivity::GameActivity(cInstance, {env->GetStringUTFChars(username, 0)});

    delete address;
    delete serverConnection;
    return (jlong) gameActivity;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_uwtsd_socialrps_GameActivity_DeconstructGameActivity(JNIEnv *env, jobject thiz,
                                                                    jlong gameActivity) {
    // TODO: implement DeconstructGameActivity()
    GameActivity::GameActivity* cGameActivity = (GameActivity::GameActivity*)gameActivity;
    if(cGameActivity != nullptr)
        delete cGameActivity;
}
extern "C"
JNIEXPORT int JNICALL
Java_com_uwtsd_socialrps_GameActivity_JoinGame(JNIEnv *env, jobject thiz, jlong gameActivity) {
    // TODO: implement JoinGame()
    GameActivity::GameActivity* gameActivityInstance = (GameActivity::GameActivity*)gameActivity;
    gameActivityInstance->RegisterGame();
    return true;
}