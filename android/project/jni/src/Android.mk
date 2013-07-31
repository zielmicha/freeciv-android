LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../python/Include $(LOCAL_PATH)/../python/

LOCAL_SRC_FILES :=  \
	entrypoint.c android.c pyjnius.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf python2.7 freeciv

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
