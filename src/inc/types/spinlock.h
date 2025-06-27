#ifndef _SPIN_LOCK_H_
#define _SPIN_LOCK_H_

#include <stdint.h>

typedef struct {
    uint8_t flag;
} spinlock_t;

/**
 * Initializes a spinlock.
 *
 * @param lock Pointer to the spinlock to be initialized.
 */
void spinlock_init(spinlock_t *lock);

/**
 * Try to acquire a spinlock.
 * @param lock Pointer to the spinlock to be acquired.
 */
void spinlock_acquire(spinlock_t *lock);

/**
 * Releases a spinlock.
 * @param lock Pointer to the spinlock to be released.
 */
void spinlock_release(spinlock_t *lock);


#endif