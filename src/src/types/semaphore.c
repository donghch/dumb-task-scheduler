
#include <stdint.h>
#include <stdlib.h>
#include "types/semaphore.h"
#include "types/lock.h"
#include "types/condvar.h"


void sem_init(sem_t *sem, int8_t initial_value) {
    if (sem == NULL) 
        return;
    sem->value = initial_value;
    lock_init(&sem->lock);
}

void sem_wait(sem_t *sem) {
    if (sem == NULL) {
        return;
    }
    lock_acquire(&sem->lock);
    while (sem->value <= 0) {
        cond_wait(&sem->condvar, &sem->lock);
    }
    sem->value--;
    lock_release(&sem->lock);
}

void sem_post(sem_t *sem) {
    if (sem == NULL) {
        return;
    }
    lock_acquire(&sem->lock);
    sem->value++;
    cond_signal(&sem->condvar);
    lock_release(&sem->lock);
}