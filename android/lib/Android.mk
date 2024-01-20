LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := app
LOCAL_CFLAGS := -Wall
LOCAL_SRC_FILES := main.c libui.c
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_LDLIBS += -llog

LOCAL_SRC_FILES += ../../src/int.c

include $(BUILD_SHARED_LIBRARY)
