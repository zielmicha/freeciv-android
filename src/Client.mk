# Client.mk is used by genMakefile.sh to generate src/Android.mk (android/project/jni/freeciv-client/Android.mk)

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := freeciv-client
LOCAL_SRC_FILES := LIST_OF_LOCAL_SRC_FILES

LOCAL_LDLIBS    := -lz -lm
LOCAL_SHARED_LIBRARIES := python2.7 curl SDL2 SDL2_mixer
LOCAL_C_INCLUDES    := $(LOCAL_PATH)/py_integration $(LOCAL_PATH)/client $(LOCAL_PATH)/client/include $(LOCAL_PATH)/client/agents $(LOCAL_PATH)/client/luascript $(LOCAL_PATH)/common $(LOCAL_PATH)/ai $(LOCAL_PATH)/ai/classic $(LOCAL_PATH)/ai/default $(LOCAL_PATH)/ai/threaded $(LOCAL_PATH)/common/aicore $(LOCAL_PATH)/common/scriptcore $(LOCAL_PATH)/utility $(LOCAL_PATH)/server $(LOCAL_PATH)/server/advisors $(LOCAL_PATH)/server/generator $(LOCAL_PATH)/server/scripting $(LOCAL_PATH)/dependencies/lua-5.3/src $(LOCAL_PATH)/dependencies/tolua-5.2/include $(LOCAL_PATH)/dependencies/cvercmp $(LOCAL_PATH) jni/python/Include jni/python jni/curl/include
LOCAL_CFLAGS	:= -DHAVE_CONFIG_H -DSDL2_PLAIN_INCLUDE

include $(BUILD_SHARED_LIBRARY)
