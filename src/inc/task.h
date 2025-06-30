#ifndef _TASK_H_
#define _TASK_H_

#include <stdint.h>
#include <stdbool.h>
#include "hardware/cortex-m3/context.h"

typedef enum {
    TASK_STATE_READY,
    TASK_STATE_RUNNING,
    TASK_STATE_SLEEPING,
    TASK_STATE_BLOCKED
} task_state_t;

typedef struct {
    void (*task)(void** args);
    uint8_t priority;
    uint32_t stack_size;
    uint32_t sleep_time;
    void *stack_top;
    context_t context;
    bool has_ran;
    task_state_t state;
} task_t;



#endif