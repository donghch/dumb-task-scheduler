#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include <stdint.h>
#include "lock.h"
#include "condvar.h"

typedef struct {
    int8_t value;
    lock_t lock;
    cond_t condvar;
} sem_t;

/**
 * Initializes a semaphore.
 * @param sem Pointer to the semaphore to initialize.
 */
void sem_init(sem_t *sem, int8_t initial_value);

/**
 * Wait on a semaphore.
 * This function blocks until the semaphore's value is greater than zero,
 * @param sem Pointer to the semaphore to wait on.
 */
void sem_wait(sem_t *sem);

/**
 * Post (signal) a semaphore.
 * This function increments the semaphore's value, potentially waking up a waiting thread.
 * @param sem Pointer to the semaphore to post.
 */
void sem_post(sem_t *sem);

#endif