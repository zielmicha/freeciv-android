#include <Python.h>
#include <android/log.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <com_zielm_p4a_Wrapper.h>

void initgraphics();
void initandroid();
void initfreecivclient();
void initjnius();

void* SDL_ANDROID_GetJNIEnv() {
  /* make pyjnius happy */
  return NULL;
}

JNIEXPORT void JNICALL Java_com_zielm_p4a_Wrapper_init0
(JNIEnv* env, jclass class, jstring jPythonPath) {
  const char* pythonHome = (*env)->GetStringUTFChars(env, jPythonPath, 0);
  __android_log_write(ANDROID_LOG_INFO, "entrypoint.c", "starting Python");
  //freopen("/sdcard/entrypoint.c.log", "a", stdout);
  //freopen("/sdcard/entrypoint.c.log", "a", stderr);

  setenv("PYTHONHOME", pythonHome, 1);
  char* pythonpath = malloc(strlen(pythonHome) + 100);
  strcpy(pythonpath, pythonHome);
  strcat(pythonpath, "/lib/python2.7");
  setenv("PYTHONPATH", pythonpath, 1);
  __android_log_print(ANDROID_LOG_INFO, "entrypoint.c", "PYTHONPATH: %s", pythonpath);

  Py_Initialize();
  PyRun_SimpleString("print 'Python running'");
  __android_log_write(ANDROID_LOG_INFO, "entrypoint.c", "loading code");
  initjnius();
  initandroid();
  initfreecivclient();
  __android_log_write(ANDROID_LOG_INFO, "entrypoint.c", "starting application");
  PyRun_SimpleString("import android; android.main()");
  Py_Finalize();
  exit(0);
}
