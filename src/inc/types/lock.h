#ifndef _LOCK_H_
#define _LOCK_H_

#include <stdint.h>
#include "spinlock.h"
#include "task-queue.h"

typedef struct {
    spinlock_t guard;
    uint8_t flag;
    task_queue_t wait_queue;
} lock_t;

/**
 * Initializes a lock.
 * @param lock Pointer to the lock to be initialized.
 * @param wait_queue_capacity The maximum number of tasks that can wait for the lock.
 * @return 0 on success, -1 if the arguments are invalid, -2 if not enough memory
 */
int lock_init(lock_t *lock, uint8_t wait_queue_capacity);

/**
 * Deinitializes a lock.
 * @param lock Pointer to the lock to be deinitialized.
 * @return 0 on success, -1 if the arguments are invalid.
 */
int lock_deinit(lock_t *lock);

/**
 * Try to acquire a lock.
 * @param lock Pointer to the lock to be acquired.
 */
void lock_acquire(lock_t *lock);

/**
 * Releases a lock.
 * @param lock Pointer to the lock to be released.
 */
void lock_release(lock_t *lock);


#endif