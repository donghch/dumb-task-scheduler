/**
 * @file task_queue.h
 * @brief Header file for the task queue implementation.
 * This file defines the structure and functions for managing a queue of tasks.
 */

#ifndef _TASK_QUEUE_H_
#define _TASK_QUEUE_H_

#include "task.h"
#include "def.h"
#include <stdint.h>

/**
 * @brief Structure representing a task queue.
 */
typedef struct {
    task_t *tasks;
    uint8_t capacity;
    uint8_t size;
    uint8_t head;
    uint8_t tail;
} task_queue_t;

/**
 * @brief Initialize a task queue.
 * 
 * @param queue Pointer to the task queue to be initialized.
 * @param capacity Maximum number of tasks the queue can hold.
 * @param tasks_array Pointer to an array of tasks that will be used by the queue.
 */
void task_queue_init(task_queue_t *queue, uint8_t capacity, task_t *tasks_array);

/**
 * @brief Insert a task into the task queue.
 * 
 * @param queue Pointer to the task queue.
 * @param task Pointer to the task to be inserted.
 * @return int Returns 0 on success, -1 if the queue is full.
 */
int task_queue_push(task_queue_t *queue, task_t *task);

/**
 * @brief Remove a task from the task queue.
 * 
 * @param queue Pointer to the task queue.
 * @return None
 */
void task_queue_pop(task_queue_t *queue);


/**
 * @brief Access the task at the front of the task queue without removing it.
 * 
 * @param queue Pointer to the task queue.
 * @return task_t* Pointer to the task at the front of the queue, or NULL
 */
task_t *task_queue_head(task_queue_t *queue);


#endif