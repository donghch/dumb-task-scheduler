#include "types/task-queue.h"
#include <stdlib.h>
#include <string.h>

int task_queue_init(task_queue_t *queue, uint8_t capacity) {

    if (queue == NULL || capacity == 0) {
        return -1; // Invalid parameters
    }

    queue->tasks = (task_t **)malloc(capacity * sizeof(task_t *));
    if (queue->tasks == NULL) {
        return -1; // Memory allocation failed
    }
    memset(queue->tasks, 0, capacity * sizeof(task_t *));

    queue->capacity = capacity;
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;

    return 0;
}

int task_queue_deinit(task_queue_t *queue) {

    if (queue == NULL) {
        return -1;
    }

    free(queue->tasks);
    queue->tasks = NULL;

    queue->capacity = 0;
    queue->size = 0;
    queue->head = 0;
    queue->tail = 0;    

    return 0;
}

int task_queue_push(task_queue_t *queue, task_t *task) {

    if (queue == NULL || task == NULL) {
        return -2; // Invalid parameters
    }
    
    if (queue->size >= queue->capacity) {
        return -1; // Queue is full, cannot push new task
    }
    
    queue->tasks[queue->tail] = task; // Copy the task into the queue
    queue->tail = (queue->tail + 1) % queue->capacity; // Update tail index
    queue->size++;
    
    return 0; // Success
}

void task_queue_pop(task_queue_t *queue) {
    if (queue->size == 0) {
        return; // Queue is empty, nothing to pop
    }
    
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;
}

task_t *task_queue_head(task_queue_t *queue) {
    if (queue->size == 0) {
        return NULL; // Queue is empty, no head task
    }
    
    return queue->tasks[queue->head];
}