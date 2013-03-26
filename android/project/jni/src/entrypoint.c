#include <Python.h>
#include <android/log.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int SDL_main() {
  __android_log_write(ANDROID_LOG_ERROR, "freeciv_entrypoint", "all ok, testing");
  char cwd[1024];
  getcwd(cwd, 1024);
  fprintf(stderr, "pwd %s\n", cwd);
  //putenv("PYTHONHOME", "", 1);

  Py_SetProgramName("android");
  Py_Initialize();
  PyRun_SimpleString("print 'foobar'");
  Py_Finalize();

  __android_log_write(ANDROID_LOG_ERROR, "freeciv_entrypoint", "Python ran");

  exit(0);
}
