#include "task.h"
#include <stdlib.h>
#include "types/task-queue.h"
#include "def.h"

extern task_queue_t task_queue;
extern task_t idle;

/**
 * Selects the next task to run based on the scheduling algorithm.
 * This function is a placeholder and should be implemented according to the specific scheduling algorithm.
 * 
 * @return Pointer to the next task to run, or NULL if no task is available.
 */
task_t *select_next_task() {
    task_t *next_task = task_queue_head(&task_queue);

    while (next_task != NULL && next_task->state != TASK_STATE_READY) {
        task_queue_pop(&task_queue);
        task_queue_push(&task_queue, next_task);
        next_task = task_queue_head(&task_queue);
    }
    
    return next_task;
}

/**
 * Freezes the current task, saving its state and preparing it for later resumption.
 * This function is a placeholder and should be implemented according to the specific scheduling algorithm.
 * 
 * @return 0 on success, or an error code if the operation fails.
 */
int freeze_current_task() {
    return 0;
}