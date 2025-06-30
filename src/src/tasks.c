
#include "types/spinlock.h"
#include "types/lock.h"

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

static int counter = 0;

void idle_task(void** args) {
    int a = 0;

    lock_acquire(&lc);
    while (a < 5) {
        a++;
        counter++;
    }
    lock_release(&lc);

    while (1) {
        ;
    }
}

void dumb_task(void **args) {
    int b = 0;
    lock_acquire(&lc);
    while (b < 5) {
        b++;
        counter++;
    }
    lock_release(&lc);
    while (1) {
        ;
    }
}

void random_task(void **args) {
    int c = 0;
    lock_acquire(&lc);
    while (c < 5) {
        c++;
        counter++;
    }
    lock_release(&lc);
    while (1) {
        ;
    }
}