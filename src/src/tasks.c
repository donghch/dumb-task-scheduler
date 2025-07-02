
#include "types/spinlock.h"
#include "types/lock.h"
#include "types/condvar.h"

spinlock_t lock;
task_t *wait_array[10];
lock_t lc = {
    .guard = {0},
    .flag = 0,
    .wait_queue = {
        .tasks = wait_array,
        .capacity = 10,
        .size = 0,
        .head = 0,
        .tail = 0
    }
};

cond_t cond;

static int counter = 0;

void idle_task(void** args) {

    while (1) {
        asm ("SVC #158");
    }
}

void dumb_task(void **args) {
    lock_acquire(&lc);
    while (counter < 15000) {
        counter++;
    }
    cond_signal(&cond);
    lock_release(&lc);
    while (1) {
        ;
    }
}

void random_task(void **args) {
    int c = 0;
    lock_acquire(&lc);
    while (counter < 15000) {
        cond_wait(&cond, &lc);
    }
    lock_release(&lc);
    while (1) {
        ;
    }
}