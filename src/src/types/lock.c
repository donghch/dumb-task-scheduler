#include <stdlib.h>
#include <stdint.h>
#include "types/lock.h"
#include "types/spinlock.h"
#include "types/task-queue.h"

extern task_t *current_task;

int lock_init(lock_t *lock, uint8_t wait_queue_capacity) {

    if (lock == NULL || wait_queue_capacity == 0) {
        return -1; // Invalid arguments
    }

    lock->flag = 0;
    spinlock_init(&lock->guard);
    if (task_queue_init(&lock->wait_queue, wait_queue_capacity) != 0) {
        return -2; // Not enough memory
    }

    return 0; // Success
}

int lock_deinit(lock_t *lock) {

    if (lock == NULL)
        return -1;

    lock->flag = 0;
    lock->guard.flag = 0;
    task_queue_deinit(&lock->wait_queue);
    lock->wait_queue.size = 0;
    lock->wait_queue.head = 0;
    lock->wait_queue.tail = 0;
    lock->wait_queue.capacity = 0;
    lock->wait_queue.tasks = NULL;

    return 0;
}

void lock_acquire(lock_t *lock) {
    if (lock == NULL) {
        return;
    }

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