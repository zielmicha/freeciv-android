#include <fcparallel.h>
#include <thpool.h>
#include <semaphore.h>
#include <stdio.h>

static fcparallel_task tasks[5120];
static int task_count = 0;
static sem_t end_of_tasks;
static thpool_t* pool = 0;

void fcparallel_add_task(void* func, int argcount, void* arg1, void* arg2) {
  fcparallel_task* task = &tasks[task_count++];
  task->func = func;
  task->argcount = argcount;
  task->arg1 = arg1;
  task->arg2 = arg2;
}
void fcparallel_start() {
  task_count = 0;
  if(!pool)
    pool = thpool_init(4);
}

static void callfunc(fcparallel_task* task) {
  if(task->argcount == 0) {
    void (*func)() = task->func;
    func();
  } else if(task->argcount == 1) {
    void (*func)(void*) = task->func;
    func(task->arg1);
  } else if(task->argcount == 2) {
    void (*func)(void*, void*) = task->func;
    func(task->arg1, task->arg2);
  }
}

static void fcparallel_work(fcparallel_task* task) {
  //printf("work is being done...\n");
  callfunc(task);
  sem_post(&end_of_tasks);
}

void fcparallel_end() {
  sem_init(&end_of_tasks, 0, task_count);
  printf("executing %d tasks...\n", task_count);

  int i;

  for(i=0; i<task_count; i++)
    thpool_add_work(pool, (void*)fcparallel_work, (void*)(&tasks[i]));

  sem_wait(&end_of_tasks);
  sem_destroy(&end_of_tasks);
}
