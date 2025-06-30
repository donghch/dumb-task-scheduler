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
 * * @param lock Pointer to the lock to be initialized.
 */
void lock_init(lock_t *lock);

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