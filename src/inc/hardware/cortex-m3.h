#ifndef _CORTEX_M3_H_
#define _CORTEX_M3_H_

#include <stdint.h>

/* Autosaved context definition */
typedef struct {
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
    uint32_t lr; 
    uint32_t sp;
    uint32_t pc;
    uint32_t psr;
} context_t;

#endif