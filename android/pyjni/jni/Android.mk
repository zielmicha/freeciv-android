# client makefile

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := pyjni
LOCAL_SRC_FILES := pyjni.c
LOCAL_CFLAGS    := -I../../src/python-include -I. -DHAVE_CONFIG_H -DANDROID
LOCAL_LDLIBS    := -L../.. -L.. -lpython2.7 -llog -lsdl

include $(BUILD_SHARED_LIBRARY)