/**
 * @file task-priority-queue.h
 * @brief This file defines the structure and functions for managing a priority queue of tasks.
 */

#ifndef _TASK_PRIORITY_QUEUE_H_
#define _TASK_PRIORITY_QUEUE_H_

#include "task.h"
#include "def.h"

typedef struct {
    task_t *task_arr;
    uint8_t capacity;
    uint8_t size;
} task_pool_t;

/**
 * @brief Setup task pool.
 * This function initializes a task pool with a specified capacity and an array of tasks.
 * @param pool Pointer to the task pool to be initialized.
 * @param capacity The maximum number of tasks the pool can hold.
 * @param task_array Pointer to an array of tasks that will be used by the pool.
 * @return int Returns 0 on success, or -1 if initialization fails due to invalid parameters.
 */
int task_pool_init(task_pool_t *pool, uint8_t capacity, task_t *task_array);

/**
 * @brief Insert a task into the task pool.
 * This function adds a task to the pool, ensuring that the pool does not exceed its capacity.
 * @param pool Pointer to the task pool.
 * @param task Pointer to the task to be added.
 * @return int Returns 0 on success, -1 if the pool is full, or -2 if invalid parameters are provided.
 */
int task_pool_add(task_pool_t *pool, task_t *task);

/**
 * @brief Get the next task from the task pool.
 * This function retrieves the next task from the pool based on task picking policy.
 * @param pool Pointer to the task pool.
 * 
 * @return task_t* Pointer to the next task in the pool, or NULL if no tasks are available.
 */
task_t *task_pool_getnext(task_pool_t *pool);

/**
 * @brief Remove a task from the task pool.
 * This function removes a specified task from the pool.
 * @param pool Pointer to the task pool.
 * @param task Pointer to the task to be removed.
 */
void task_pool_remove(task_pool_t *pool, task_t *task);

#endif