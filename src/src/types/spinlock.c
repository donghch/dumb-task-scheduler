#include "types/spinlock.h"


void spinlock_init(spinlock_t *lock) {
    lock->flag = 0;
}