
#include "task.h"
#include "def.h"

#include <stdlib.h>
#include <stdint.h>

static struct task_t task_array[SCHEDULER_TASK_ARRAY_SIZE];

struct task_t *current_task = NULL;

void idle_task(void **args);

static uint8_t idle_task_stack[IDLE_TASK_STACK_SIZE] __attribute__((aligned(8)));
static struct task_t idle = {
    .task = idle_task,
    .priority = 0,
    .stack_size = IDLE_TASK_STACK_SIZE,
    .sleep_time = 0,
    .stack = idle_task_stack,
    .regstate = {},
    .has_ran = false
};

void idle_task(void** args) {
    int a = 0;
    while (1) {
        a++;
    }
}

/* Scheduler Functions */

void schedler_init(void) {
    for (int i = 0; i < SCHEDULER_TASK_ARRAY_SIZE; i++) {
        task_array[i].task = NULL;
        task_array[i].priority = 0;
        task_array[i].stack_size = 0;
        task_array[i].sleep_time = 0;
        task_array[i].stack = NULL;
        task_array[i].has_ran = false;
    }
    current_task = &task_array[0]; // Set the first task as the current task
}

struct task_t *scheduler_add_task(void (*task)(void **args), uint8_t priority, void *stack) {
    for (int i = 0; i < SCHEDULER_TASK_ARRAY_SIZE; i++) {
        if (task_array[i].task == NULL) {
            task_array[i].task = task;
            task_array[i].priority = priority;
            task_array[i].stack_size = 0; // Assuming a predefined stack size
            task_array[i].sleep_time = 0; // Default to no sleep
            task_array[i].stack = stack;
            task_array[i].has_ran = false;
            return &task_array[i];
        }
    }
    return NULL; // No available slot for the new task
}

void scheduler_start(void) {
    // Start the scheduler (this is a placeholder, actual implementation may vary)
    while (1) {
        // Scheduler loop to manage tasks
        for (int i = 0; i < SCHEDULER_TASK_ARRAY_SIZE; i++) {
            if (task_array[i].task != NULL && !task_array[i].has_ran) {
                current_task = &task_array[i];
                current_task->task(NULL); // Execute the task
                current_task->has_ran = true; // Mark as ran
            }
        }
    }
}

