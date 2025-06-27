
#include "task.h"
#include "def.h"
#include "types/task-queue.h"
#include "hardware/cortex-m3.h"

#include <stdlib.h>
#include <stdint.h>

static task_t task_array[SCHEDULER_TASK_ARRAY_SIZE];
task_queue_t task_queue;
context_t current_context;
task_t *current_task = NULL;

extern void start_systick(void);
task_t *scheduler_add_task(void (*task)(void **args), uint8_t priority, void *stack, uint32_t stack_size);

static void idle_task(void **args);

static uint8_t idle_task_stack[IDLE_TASK_STACK_SIZE] __attribute__((aligned(8)));

void idle_task(void** args) {
    int a = 0;
    while (a < 10000) {
        a++;
    }

    while (1) {
        a = a;
    }
}

/* Scheduler Functions */

void schedler_init(void) {
    task_queue_init(&task_queue, SCHEDULER_TASK_ARRAY_SIZE, task_array);
    scheduler_add_task(idle_task, 0, idle_task_stack, IDLE_TASK_STACK_SIZE);
}

void scheduler_task_stack_init(task_t *task);

task_t *scheduler_add_task(void (*task)(void **args), uint8_t priority, void *stack, uint32_t stack_size) {

    int err;

    task_t new_task =  {
        .task = task, 
        .priority = priority,
        .stack_size = stack_size,
        .sleep_time = 0,
        .stack_top = stack + stack_size,
        .has_ran = false
    };

    err = task_queue_push(&task_queue, &new_task);
    if (err != 0) {
        return NULL; // Error adding task
    }
    return &new_task; // Return the newly added task
}

extern void scheduler_load_task(void *stacktop, void (*task)(void **args));

void scheduler_start(void) {
    // Start the scheduler (this is a placeholder, actual implementation may vary)
    int a = 0;
    start_systick();
    current_task = &task_queue.tasks[0];
    scheduler_load_task(idle_task_stack + IDLE_TASK_STACK_SIZE, idle_task);
    // it should never reach here
}

void scheduler_task_stack_init(task_t *task) {
    task->context.r0 = 0;
    task->context.r1 = 0;
    task->context.r2 = 0;
    task->context.r3 = 0;
    task->context.r4 = 0;
    task->context.r5 = 0;
    task->context.r6 = 0;
    task->context.r7 = 0;
    task->context.r8 = 0;
    task->context.r9 = 0;
    task->context.r10 = 0;
    task->context.r11 = 0;
    task->context.r12 = 0;
    task->context.lr = 0;
    task->context.sp = (uint32_t)task->stack_top;
    task->context.pc = (uint32_t)task->task;
    task->context.psr = 0x21000000;
}


extern void startup(void); 
