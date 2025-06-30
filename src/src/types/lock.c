#include "types/lock.h"
#include "types/spinlock.h"
#include <stdlib.h>

extern task_t *current_task;

void lock_init(lock_t *lock) {
    if (lock != NULL) {
        spinlock_init(&lock->guard);
        lock->flag = 0;
    }
}

void lock_acquire(lock_t *lock) {
    if (lock == NULL) {
        return;
    }

    while (1) {
        spinlock_acquire(&lock->guard);
        if (lock->flag == 0) {
            lock->flag = 1;
            spinlock_release(&lock->guard);
            return;
        } else {
            current_task->state = TASK_STATE_SLEEPING;
            task_queue_push(&lock->wait_queue, current_task);
            spinlock_release(&lock->guard);
            asm ("SVC #158");
        }
    }
}

void lock_release(lock_t *lock) {
    if (lock == NULL) {
        return;
    }

    spinlock_acquire(&lock->guard);
    if (lock->wait_queue.size > 0) {
        task_t *next_task = task_queue_head(&lock->wait_queue);
        task_queue_pop(&lock->wait_queue);
        next_task->state = TASK_STATE_READY;
    } else {
        lock->flag = 0;
    }
    spinlock_release(&lock->guard);
}