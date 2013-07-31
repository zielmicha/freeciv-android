#include <Python.h>
#include <android/log.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void initgraphics();
void initandroid();
void initfreecivclient();
void initjnius();

static char* storage;

void* SDL_ANDROID_GetJNIEnv() {
  /* make pyjnius happy */
  return NULL;
}
