
#include <stdint.h>
#include "hardware/cortex-m3/context.h"
#include "hardware/cortex-m3/def.h"
#include "types/syscall.h"

void syscall_handler_c(uint8_t num, context_t *context) {
    switch (num) {
        case SYSCALL_YIELD:
            SYS_CTRL_ICSR |= (1 << 28);
            break;
        default:
            break;
    }
}