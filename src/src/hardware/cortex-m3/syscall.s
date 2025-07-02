
    .syntax unified
    .cpu cortex-m3
    .thumb
    .section .text
    .global syscall
    .global syscall_handler
    .global syscall_handler_c
    .extern current_context
    .extern save_context
    .extern load_context

    .thumb_func
    .type syscall_handler, %function
syscall_handler:

    # atomic
    PUSH {r4}
    MOV r4, #1
    MSR FAULTMASK, r4

    PUSH {lr}
    BL save_context

    # Get SVC number
    LDR r1, =current_context
    LDR r1, [r1, #60]
    SUB r1, r1, #2
    LDRB r0, [r1]
    # get context pointer
    LDR r1, =current_context
    BL syscall_handler_c
    POP {lr}

    MOV r4, #0
    MSR FAULTMASK, r4
    POP {r4}
    BX lr