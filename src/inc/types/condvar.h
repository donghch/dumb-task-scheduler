#ifndef _CONDVAR_H_
#define _CONDVAR_H_

#include "types/lock.h"
#include "task.h"

typedef struct {
    task_t *waiting_task;
} cond_t; 

/**
 * @brief Wait on a condition variable.
 * This function blocks the calling task until the condition variable is signaled.
 * It releases the associated lock while waiting.
 * @param cond Pointer to the condition variable.
 * @param lock Pointer to the lock that should be held while waiting.
 */
void cond_wait(cond_t *cond, lock_t *lock);

/**
 * @brief Signal a condition variable.
 * This function wakes up one task that is waiting on the condition variable.
 * If no tasks are waiting, it does nothing.
 * @param cond Pointer to the condition variable.
 */
void cond_signal(cond_t *cond);

#endif 