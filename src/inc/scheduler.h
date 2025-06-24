#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "task.h"

void scheduler_init(void);

struct task_t *scheduler_add_task(void (*task)(void** args), uint8_t priority, uint32_t stack_size);

void scheduler_start(void);

#endif