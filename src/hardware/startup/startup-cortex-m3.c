#include <stdint.h>


// cortex m3
extern int main(void);

extern int systick_handler(void);

extern uint32_t __stacktop; // Defined in linker script
void startup(void);

const uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    (uint32_t)(&__stacktop),      // Initial stack pointer
    (uint32_t)(main),  // Reset handler
    (uint32_t)0x3,    // NMI handler
    (uint32_t)0x4, // Hard Fault handler
    (uint32_t)0x5, // Memory Management Fault handler
    (uint32_t)0x6, // Bus Fault handler
    (uint32_t)0x7, // Usage Fault handler
    (uint32_t)0x8, // Reserved
    (uint32_t)0x9, // Reserved
    (uint32_t)0xA, // Reserved
    (uint32_t)0xB, // Reserved
    (uint32_t)0xC, // SVCall handler
    (uint32_t)0xD, // Debug Monitor handler
    (uint32_t)0xE, // Reserved
    (uint32_t)0xF, // PendSV handler
    (uint32_t)(systick_handler), // SysTick handler
    // Add other exception handlers here
};

extern uint32_t __data_start;
extern uint32_t __data_end;
extern uint32_t __data_load;
extern uint32_t __bss_start;
extern uint32_t __bss_end;

void startup(void) {

    // copy data section
    uint32_t *p = &__data_start;
    uint32_t *q = &__data_load;
    while (p < &__data_end) {
        *p++ = *q++;
    }

    // zero bss section
    p = &__bss_start;
    while (p < &__bss_end) {
        *p++ = 0;
    }

    // Call main function
    main();
}