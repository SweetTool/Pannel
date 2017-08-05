//
// Created by lucky on 05/08/2017.
//
#include "jni_device_helper.h"

#include "android_system_utils.h"
#include "common.h"

namespace PANNEL_DEVICE_HELPER {
    const char classPath[] = "org/penny/DeviceHelper";
    JNINativeMethod methods[] = {
            {"native_getBootTime", "()J", (void *) native_getBootTime}
    };
    int size = sizeof(methods) / sizeof(methods[0]);
}

jlong native_getBootTime(JNIEnv *, jclass) {
    return android_system_utils::getBootTime();
}
