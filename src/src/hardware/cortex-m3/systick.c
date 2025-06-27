
#include <stdint.h>

#define SYSTICK_TIMER_BASE 0xE000E010
#define SYST_CSR (*(volatile uint32_t *)(SYSTICK_TIMER_BASE + 0x00))
#define SYST_RVR (*(volatile uint32_t *)(SYSTICK_TIMER_BASE + 0x04))
#define SYST_CVR (*(volatile uint32_t *)(SYSTICK_TIMER_BASE + 0x08))
#define SYST_CALIB (*(volatile uint32_t *)(SYSTICK_TIMER_BASE + 0x0C))

void start_systick(void) {

    // Set the reload value to 1 second (assuming a 1 MHz clock)
    SYST_RVR = 50000 - 1; // Reload value for 1 second
    SYST_CVR = 0;           // Clear the current value register
    SYST_CSR = 0x07;       // Enable the timer, enable interrupts, and use the processor clock

}