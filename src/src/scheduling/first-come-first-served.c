#include "task.h"
#include <stdlib.h>
#include "types/task-queue.h"
#include "def.h"

extern task_queue_t task_queue;

/**
 * Selects the next task to run based on the scheduling algorithm.
 * This function is a placeholder and should be implemented according to the specific scheduling algorithm.
 * 
 * @return Pointer to the next task to run, or NULL if no task is available.
 */
task_t *select_next_task() {
    task_queue_t *queue = &task_queue;
    return (queue->size > 0) ? &queue->tasks[queue->head] : NULL;
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