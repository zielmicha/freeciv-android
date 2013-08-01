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

static JNIEnv* python_thread_jnienv;

void* SDL_ANDROID_GetJNIEnv() {
  /* make pyjnius happy */
  return python_thread_jnienv;
}

JNIEXPORT void JNICALL Java_com_zielm_p4a_Wrapper_init0
(JNIEnv* env, jclass class, jstring jPythonPath) {
  python_thread_jnienv = env;
  const char* python_home = (*env)->GetStringUTFChars(env, jPythonPath, 0);
  __android_log_write(ANDROID_LOG_INFO, "entrypoint.c", "starting Python");

  setenv("PYTHONHOME", python_home, 1);
  char* pythonpath = malloc(strlen(python_home) + 100);
  strcpy(pythonpath, python_home);
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
