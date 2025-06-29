/**
 * @file scheduler.c
 * @brief Implementation of the task scheduler.
 */
#include "task.h"
#include "def.h"
#include "types/task-queue.h"
#include "hardware/cortex-m3/context.h"

#include <stdlib.h>
#include <stdint.h>

/* Scheduler Data */
task_queue_t task_queue;
context_t current_context;
task_t *current_task = NULL;
static uint8_t idle_task_stack[IDLE_TASK_STACK_SIZE] __attribute__((aligned(8)));
static uint8_t dumb_task_stack[IDLE_TASK_STACK_SIZE] __attribute__((aligned(8)));
static uint8_t random_task_stack[IDLE_TASK_STACK_SIZE] __attribute__((aligned(8)));
static task_t task_array[SCHEDULER_TASK_ARRAY_SIZE];

/* Scheduler Function Declarations */
task_t *scheduler_add_task(void (*task)(void **args), uint8_t priority, void *stack, uint32_t stack_size);
extern void idle_task(void **args);
extern void dumb_task(void **args);
extern void random_task(void **args);
extern void start_systick(void);
extern void scheduler_load_task(void *stacktop, void (*task)(void **args));
void scheduler_task_stack_init(task_t *task);

task_t idle = {
    .task = idle_task,
    .priority = 0,
    .stack_size = IDLE_TASK_STACK_SIZE,
    .sleep_time = 0,
    .stack_top = idle_task_stack + IDLE_TASK_STACK_SIZE,
    .has_ran = false
};

/* Scheduler Functions */

/**
 * @brief Initializes the scheduler.
 * 
 * This function initializes the task queue and adds the idle task to the scheduler.
 */
void schedler_init(void) {
    task_queue_init(&task_queue, SCHEDULER_TASK_ARRAY_SIZE, task_array);
    scheduler_add_task(dumb_task, 0, dumb_task_stack, IDLE_TASK_STACK_SIZE);
    scheduler_add_task(random_task, 0, random_task_stack, IDLE_TASK_STACK_SIZE);
}

/**
 * @brief Adds a task to the scheduler.
 * 
 * @param task The function pointer to the task to be added.
 * @param priority The priority of the task.
 * @param stack Pointer to the stack memory for the task.
 * @param stack_size Size of the stack memory for the task.
 * @return Pointer to the newly added task, or NULL if an error occurred.
 */
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

    scheduler_task_stack_init(&new_task);
    err = task_queue_push(&task_queue, &new_task);
    if (err != 0) {
        return NULL; // Error adding task
    }
    return &new_task; // Return the newly added task
}


/**
 * @brief Starts the scheduler.
 * 
 * This function initializes the idle task and starts the scheduler.
 * It should never return.
 */
void scheduler_start(void) {
    // Start the scheduler (this is a placeholder, actual implementation may vary)
    int a = 0;
    current_task = &idle; 
    scheduler_task_stack_init(&idle);
    start_systick();
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
