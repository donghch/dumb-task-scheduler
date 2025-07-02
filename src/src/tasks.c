#include <stdlib.h>
#include "types/spinlock.h"
#include "types/lock.h"
#include "types/condvar.h"
#include "types/semaphore.h"

spinlock_t lock;
task_t *wait_array[10];
sem_t sem = {
    .value = 0,
    .lock = {
        .guard = {0},
        .flag = 0,
        .wait_queue = {
            .tasks = wait_array,
            .capacity = 10,
            .size = 0,
            .head = 0,
            .tail = 0
        }
    },
    .condvar = {NULL}
};

cond_t cond;

static int counter = 0;

void idle_task(void** args) {

    while (1) {
        asm ("SVC #158");
    }
}

void dumb_task(void **args) {
    while (counter < 15000) {
        counter++;
    }
    sem_post(&sem);
    while (1) {
        ;
    }
}

void random_task(void **args) {
    int c = 0;
    sem_wait(&sem);
    sem_post(&sem);
    while (1) {
        ;
    }
}