#include <Python.h>
#include <SDL.h>
#include <android/log.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "unarchive.h"

void initgraphics();
void initandroid();
void initfreecivclient();

int SDL_main(int argc, char** argv) {
  __android_log_write(ANDROID_LOG_INFO, "freeciv", "starting SDL_main");
  const char* storage = SDL_AndroidGetInternalStoragePath();
  setenv("PYTHONHOME", storage, 1);
  char* pythonpath = malloc(strlen(storage) + 100);
  strcpy(pythonpath, storage);
  strcat(pythonpath, "/lib/python2.7");
  setenv("PYTHONPATH", pythonpath, 1);

  SDL_RWops* ops = SDL_RWFromFile("code.archive", "rb");
  if(ops == NULL) {
    __android_log_write(ANDROID_LOG_ERROR, "freeciv", "opening assets failed");
  }
  unarchive(ops, storage);
  SDL_RWclose(ops);

  Py_Initialize();
  PyRun_SimpleString("print 'Python running'");
  initgraphics();
  initandroid();
  initfreecivclient();
  PyRun_SimpleString("import android; android.main()");
  Py_Finalize();

  __android_log_write(ANDROID_LOG_INFO, "freeciv", "closing app");

  exit(0);
}
