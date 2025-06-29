#include <stdint.h>
#include "task.h"
#include "hardware/cortex-m3/context.h"
#include "hardware/cortex-m3/def.h"
#include "types/task-queue.h"


// cortex m3
extern int main(void);

extern void systick_handler(void);
extern void pendsv_handler(void);
extern void syscall_handler(void);

extern uint32_t __stacktop__; // Defined in linker script
void startup(void);
extern task_t *current_task;
extern task_queue_t task_queue;
extern task_t idle;

const uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    (uint32_t)(&__stacktop__),      // Initial stack pointer
    (uint32_t)(startup),  // Reset handler
    (uint32_t)0x3,    // NMI handler
    (uint32_t)0x4, // Hard Fault handler
    (uint32_t)0x5, // Memory Management Fault handler
    (uint32_t)0x6, // Bus Fault handler
    (uint32_t)0x7, // Usage Fault handler
    (uint32_t)0x8, // Reserved
    (uint32_t)0x9, // Reserved
    (uint32_t)0xA, // Reserved
    (uint32_t)0xB, // Reserved
    (uint32_t)(syscall_handler), // SVCall handler
    (uint32_t)0xD, // Debug Monitor handler
    (uint32_t)0xE, // Reserved
    (uint32_t)(pendsv_handler), // PendSV handler
    (uint32_t)(systick_handler), // SysTick handler
    // Add other exception handlers here
};

extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __data_load__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

void startup(void) {

    // copy data section
    uint32_t *p = &__data_start__;
    uint32_t *q = &__data_load__;
    while (p < &__data_end__) {
        *p++ = *q++;
    }

    // zero bss section
    p = &__bss_start__;
    while (p < &__bss_end__) {
        *p++ = 0;
    }

    // Call main function
    main();
}

void _exit(int status) {
    // Infinite loop to indicate exit
    while (1) {
        // Optionally, you can add code to handle the exit status
    }
}

void _close_r(int file) {
    // No operation for closing a file
}

void _lseek_r(int file, int ptr, int dir) {
    // No operation for seeking in a file
}

void _write_r(int file, const char *ptr, int len) {
    // No operation for writing to a file
}

void _read_r(int file, char *ptr, int len) {
    // No operation for reading from a file
}

void _sbrk_r(void *ptr) {
    // No operation for setting the program break
}

extern task_t *select_next_task();

void systick_handler_c(void) {
    SYS_CTRL_ICSR |= (1 << 28); // Trigger PendSV exception
}

context_t *pendsv_handler_c(context_t *context) {
    
    // retrieve next task
    current_task->context = *context;
    task_t *next_task = select_next_task();
    task_queue_pop(&task_queue);
    task_queue_push(&task_queue, current_task);
    current_task = next_task; 
    return &(next_task->context);

}