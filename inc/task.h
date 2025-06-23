#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>
#include <stdbool.h>

struct task_regstate {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r12;
    uint32_t sp;
    uint32_t lr;
    uint32_t pc;
    uint32_t psr;
    uint32_t primask;
    uint32_t faultmask;
    uint32_t basepri;
    uint32_t control;
};

struct task_t {
    void (*task)(void** args);
    uint8_t priority;
    uint32_t stack_size;
    uint32_t sleep_time;
    void *stack;
    struct task_regstate regstate;
    bool has_ran;
};



#endif