
#include <stdint.h>
extern uint32_t __heap_start__;
static uint32_t current_heap = 0;

void _exit(int status) {
    // Infinite loop to indicate exit
    while (1) {
        // Optionally, you can add code to handle the exit status
    }
}

void _close(int file) {
    // No operation for closing a file
}

void _lseek_r(int file, int ptr, int dir) {
    // No operation for seeking in a file
}

void _write(int file, const char *ptr, int len) {
    // No operation for writing to a file
}

void _read(int file, char *ptr, int len) {
    // No operation for reading from a file
}

void *_sbrk(int incr) {
    uint32_t old_heap;

    if (current_heap == 0) {
        current_heap = (uint32_t)&__heap_start__;
    }

    old_heap = current_heap;
    current_heap += incr;

    return (void *)old_heap;
}