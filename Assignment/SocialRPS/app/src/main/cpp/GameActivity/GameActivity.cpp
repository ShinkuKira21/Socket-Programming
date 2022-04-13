//
// Created by edwardpatch1 on 4/11/22.
//

#include "GameActivity.h"
#include <jni.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_uwtsd_socialrps_GameManager_PostAction(JNIEnv *env, jobject thiz, jstring player_name,
                                                jint selection) {
    // TODO: implement PostAction()
    const char* playerName = env->GetStringUTFChars(player_name, 0);
    GameActivity::GameActivity gameActivity({playerName, (int)selection});
    // return the server response

    return env->NewStringUTF("Server Response:");
}

GameActivity::GameActivity::GameActivity(ClientStructure clientInfo) {
    this->clientInfo = clientInfo;
}