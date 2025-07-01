
#include <stdint.h>
#include "hardware/cortex-m3/context.h"
#include "hardware/cortex-m3/def.h"
#include "types/condvar.h"
#include "types/lock.h"
#include "types/syscall.h"
#include "task.h"

/* cond var handling */
extern 

void syscall_handler_c(uint8_t num, context_t *context) {
    switch (num) {
        case SYSCALL_YIELD:
            SYS_CTRL_ICSR |= (1 << 28);
            break;
        case SYSCALL_CONDVAR_WAIT: 
            cond_t *cond = (cond_t *)context->r0;
            lock_t *lock = (lock_t *)context->r1;
            cond->waiting_task->state = TASK_STATE_SLEEPING;
            lock_release(lock);
            SYS_CTRL_ICSR |= (1 << 28);
            break;
        case SYSCALL_CONDVAR_SIGNAL:
            break;
        default:
            break;
    }
}