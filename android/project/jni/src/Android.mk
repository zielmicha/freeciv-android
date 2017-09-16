LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
	$(LOCAL_PATH)/../python/Include $(LOCAL_PATH)/../python/ \
	$(LOCAL_PATH)/../SDL_image $(LOCAL_PATH)/../SDL_ttf

LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	entrypoint.c unarchive.c graphics.c android.c pyjnius.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf python2.7 curl freeciv

LOCAL_LDLIBS := -lGLESv1_CM -llog

include $(BUILD_SHARED_LIBRARY)
