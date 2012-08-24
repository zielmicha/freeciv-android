
typedef struct {
  void* func;
  int argcount;
  void* arg1;
  void* arg2;
} fcparallel_task;

void fcparallel_add_task(void* func, int argcount, void* arg1, void* arg2);
void fcparallel_start();
void fcparallel_end();
