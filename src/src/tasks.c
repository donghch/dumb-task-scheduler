
#include "types/spinlock.h"

spinlock_t lock;

void idle_task(void** args) {
    int a = 0;

    spinlock_acquire(&lock);
    while (a < 5) {
        a++;
    }
    spinlock_release(&lock);

    while (1) {
        ;
    }
}

void dumb_task(void **args) {
    int b = 0;
    spinlock_acquire(&lock);
    while (b < 5) {
        b++;
    }
    spinlock_release(&lock);
    while (1) {
        ;
    }
}

void random_task(void **args) {
    int c = 0;
    spinlock_acquire(&lock);
    while (c < 5) {
        c++;
    }
    spinlock_release(&lock);
    while (1) {
        ;
    }
}