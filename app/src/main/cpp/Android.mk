LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libPannel
LOCAL_C_INCLUDES := common.h file_utils.h android_system_utils.h jni_device_helper.h
LOCAL_SRC_FILES := common.cpp native.cpp file_utils.cpp android_system_utils.cpp \
         jni_device_helper.cpp

LOCAL_LDLIBS := -llog
LOCAL_CFLAGS := -std=gnu++11

include $(BUILD_SHARED_LIBRARY)
