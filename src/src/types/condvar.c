#include <stdlib.h>
#include "types/condvar.h"
#include "task.h"

extern task_t *current_task;

void cond_wait(cond_t *cond, lock_t *lock) {

    if (cond == NULL || lock == NULL) {
        return;
    }
    cond->waiting_task = current_task;
    asm ("SVC #0"); // syscall to condvar wait
    lock_acquire(lock);
}

void cond_wait_kernel(cond_t *cond, lock_t *lock) {
    lock_release(lock);
    cond->waiting_task->state = TASK_STATE_SLEEPING;
}

void cond_signal(cond_t *cond) {
    if (cond->waiting_task == NULL) 
        return; 
    cond->waiting_task->state = TASK_STATE_READY;
    cond->waiting_task = NULL;
}

void cond_signal_kernel(cond_t *cond) {

}