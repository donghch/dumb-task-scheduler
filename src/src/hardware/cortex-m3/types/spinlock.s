    .syntax unified
    .cpu cortex-m3
    .thumb

    .section .text
    .global spinlock_acquire
    .global spinlock_release

    .thumb_func
    .type spinlock_acquire, %function
spinlock_acquire:
.spinlock_acquire_test:
    LDREXB r1, [r0]
    CMP r1, #0
    BNE .spinlock_acquire_test
    MOV r1, #1
    STREXB r2, r1, [r0]
    CMP r2, #1
    BEQ .spinlock_acquire_test
    BX lr

    .thumb_func
    .type spinlock_release, %function
spinlock_release:
    MOV r1, #0
    STRB r1, [r0]
    BX lr
