# Server.mk is used by genMakefile.sh to generate android/project/jni/freeciv-server/Android.mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := freeciv-server
LOCAL_SRC_FILES := LIST_OF_LOCAL_SRC_FILES

LOCAL_LDLIBS    := -lz -lm
LOCAL_SHARED_LIBRARIES := curl
LOCAL_C_INCLUDES    := $(LOCAL_PATH)/common $(LOCAL_PATH)/ai $(LOCAL_PATH)/ai/classic $(LOCAL_PATH)/ai/default $(LOCAL_PATH)/ai/threaded $(LOCAL_PATH)/common/aicore $(LOCAL_PATH)/common/scriptcore $(LOCAL_PATH)/utility $(LOCAL_PATH)/server $(LOCAL_PATH)/server/advisors $(LOCAL_PATH)/server/generator $(LOCAL_PATH)/server/scripting $(LOCAL_PATH)/dependencies/lua-5.3/src $(LOCAL_PATH)/dependencies/tolua-5.2/include $(LOCAL_PATH) jni/Include jni jni/curl/include
LOCAL_CFLAGS	:= -DHAVE_CONFIG_H

include $(BUILD_EXECUTABLE)
