LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := z
LOCAL_SRC_FILES := adler32.c compress.c crc32.c deflate.c gzclose.c gzlib.c gzread.c gzwrite.c infback.c inffast.c inflate.c inftrees.c minigzip.c trees.c uncompr.c zutil.c
LOCAL_CFLAGS    := -Ijni
#LOCAL_LDLIBS    := 

include $(BUILD_SHARED_LIBRARY)