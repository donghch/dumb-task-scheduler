#ifndef _DEF_H_
#define _DEF_H_

#include "task.h"
extern struct task_t *current_task;

/* Task Schedulers */
#define SCHEDULER_TASK_ARRAY_SIZE 10
#define CURRENT_TASK current_task;
#define IDLE_TASK_STACK_SIZE 256

#endif