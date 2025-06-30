#ifndef _CORTEX_M3_DEF_H_
#define _CORTEX_M3_DEF_H_

#include <stdint.h>

/* Cortex-M3 Peripherals */
#define SYS_CTRL_BLOCK_1_BASE   0XE000E008
#define SYS_TIMER_BASE          0XE000E010
#define NVIC_1_BASE             0xE000E100
#define SYS_CTRL_BLOCK_2_BASE   0xE000ED00
#define MPU_TYPE_BASE           0xE000ED90
#define MPU_CTRL_BASE           0xE000ED90
#define NVIC_2_BASE             0xE000EF00

// System Control Block (SCB) registers
#define SYS_CTRL_REG(offset) (*(volatile uint32_t *)(SYS_CTRL_BLOCK_2_BASE + (offset)))
#define SYS_CTRL_ACTLR       SYS_CTRL_BLOCK_1_BASE
#define SYS_CTRL_CPUID       SYS_CTRL_REG(0x00)
#define SYS_CTRL_ICSR        SYS_CTRL_REG(0x04)
#define SYS_CTRL_VTOR        SYS_CTRL_REG(0x08)
#define SYS_CTRL_AIRCR       SYS_CTRL_REG(0x0C)
#define SYS_CTRL_SCR         SYS_CTRL_REG(0x10)
#define SYS_CTRL_CCR         SYS_CTRL_REG(0x14)
#define SYS_CTRL_SHPR1       SYS_CTRL_REG(0x18)
#define SYS_CTRL_SHPR2       SYS_CTRL_REG(0x1C)
#define SYS_CTRL_SHPR3       SYS_CTRL_REG(0x20)
#define SYS_CTRL_SHCSR       SYS_CTRL_REG(0x24)
#define SYS_CTRL_CFSR        SYS_CTRL_REG(0x28)
#define SYS_CTRL_MMSR        SYS_CTRL_REG(0x28)
#define SYS_CTRL_BFSR        SYS_CTRL_REG(0x29)
#define SYS_CTRL_UFSR        SYS_CTRL_REG(0x2A)
#define SYS_CTRL_HFSR        SYS_CTRL_REG(0x2C)
#define SYS_CTRL_MMAR        SYS_CTRL_REG(0x34)
#define SYS_CTRL_BFAR        SYS_CTRL_REG(0x38)
#define SYS_CTRL_AFSR        SYS_CTRL_REG(0x3C)

// System Timer Registers
#define SYS_TIMER_REG(offset) (*(volatile uint32_t *)(SYS_TIMER_BASE + (offset)))
#define SYS_TIMER_CSR         SYS_TIMER_REG(0x00)
#define SYS_TIMER_RVR         SYS_TIMER_REG(0x04)
#define SYS_TIMER_CVR         SYS_TIMER_REG(0x08)
#define SYS_TIMER_CALIB       SYS_TIMER_REG(0x0C)

// NVIC Registers


// MPU Registers
#define MPU_REG(offset) (*(volatile uint32_t *)(MPU_CTRL_BASE + (offset)))
#define MPU_TYPE            MPU_REG(0x00)
#define MPU_CTRL            MPU_REG(0x04)
#define MPU_RNR             MPU_REG(0x08)
#define MPU_RBAR            MPU_REG(0x0C)
#define MPU_RASR            MPU_REG(0x10)

#endif