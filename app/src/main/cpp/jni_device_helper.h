//
// Created by lucky on 05/08/2017.
//

#ifndef JNI_DEVICE_HELPER_H
#define JNI_DEVICE_HELPER_H

#include "jni.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace PANNEL_DEVICE_HELPER{
    extern const char classPath[];
    extern JNINativeMethod methods[];
    extern int size;
}

jlong native_getBootTime(JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif

#endif // JNI_DEVICE_HELPER_H
