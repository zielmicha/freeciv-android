#include <Python.h>
#include <pyclient.h>

int
main(int argc, char *argv[])
{
  Py_Initialize();
  initfreecivclient();
  PySys_SetArgv(argc, argv);
  PyRun_SimpleFile(fopen("lib/main.py", "r"), "main.py");
  Py_Finalize();
  return 0;
}
