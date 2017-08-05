#include <cstdio>

#include "common.h"

#include "jni.h"
#include "jni_device_helper.h"

static const char TAG[] = "native";

/**
 * Register several native methods for one class.
 */
static int registerNativeMethods(JNIEnv* env, const char* className,
	JNINativeMethod* gMethods, int numMethods) {
	jclass clazz = env->FindClass(className);
	if (NULL == clazz) {
		lerror(TAG, "Native registraation unable to find class '%s'", className);
		return JNI_FALSE;
	}
	if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
		lerror(TAG, "RegisterNatives failed for '%s'", className);
		return JNI_FALSE;
	}
	return JNI_TRUE;
}

/**
 * Register native methods for all classes we know about.
 * return JNI_TRUE on success.
 */
static int registerNatives(JNIEnv* env) {
	if (!registerNativeMethods(env, PANNEL_DEVICE_HELPER::classPath, PANNEL_DEVICE_HELPER::methods, PANNEL_DEVICE_HELPER::size)) {
		return JNI_FALSE;
	}
    return JNI_TRUE;
}

// - --------------------------------------------
/**
 * This is called by the VM when the shared library is first loaded.
 */

typedef union {
	JNIEnv *env;
	void* venv;
} UnionJNIEnvToVoid;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
	UnionJNIEnvToVoid uenv;
	uenv.venv = NULL;
	jint result = -1;
	JNIEnv *env;

	ldebug(TAG, "JNI_LOAD");
	if (JNI_OK != vm->GetEnv(&uenv.venv, JNI_VERSION_1_4)) {
		lerror(TAG, "GetEnv failed.");
		goto bail;
	}
	env = uenv.env;

	if (JNI_TRUE != registerNatives(env)) {
		lerror(TAG, "RegisterNatives failed.");
		goto bail;
	}

	result = JNI_VERSION_1_4;

bail:
	return result;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
	ldebug(TAG, "JNI_OnUnload");
}
