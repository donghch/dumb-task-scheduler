
    .syntax unified
    .cpu cortex-m3
    .thumb

    .section .text
    .global systick_handler
    .global pendsv_handler
    .global save_context
    .global enter_user_mode
    .global load_context
    .global systick_handler_c
    .global pendsv_handler_c
    .extern current_context

    .thumb_func
systick_handler:
    PUSH {lr}
    BL systick_handler_c
    POP {lr}
    BX lr

    .thumb_func
pendsv_handler:
    PUSH {lr}
    BL save_context
    LDR r0, =current_context
    BL pendsv_handler_c
    BL load_context
    POP {lr}
    BX lr

    .thumb_func
save_context:
    # save all registers to current context  
    LDR r0, =current_context
    MRS r2, PSP

    # save r0-r3
    LDR r1, [r2, #0]
    STR r1, [r0]
    LDR r1, [r2, #4]
    STR r1, [r0, #4]
    LDR r1, [r2, #8]
    STR r1, [r0, #8]
    LDR r1, [r2, #12]
    STR r1, [r0, #12]
    # save r4-r11
    STR r4, [r0, #16]
    STR r5, [r0, #20]
    STR r6, [r0, #24]
    STR r7, [r0, #28]
    STR r8, [r0, #32]
    STR r9, [r0, #36]
    STR r10, [r0, #40]
    STR r11, [r0, #44]
    # save r12, lr, sp, pc, xPSR
    LDR r1, [r2, #16]
    STR r1, [r0, #48]
    LDR r1, [r2, #20]
    STR r1, [r0, #52]
    MRS r1, PSP
    STR r1, [r0, #56]
    LDR r1, [r2, #24]
    STR r1, [r0, #60]
    LDR r1, [r2, #28]
    STR r1, [r0, #64]

    BX lr

    .thumb_func
load_context:
    # restore the context
    # load back sp first
    LDR r2, [r0, #56]
    MSR PSP, r2
    ISB
    # restore r0-r3
    LDR r1, [r0]
    STR r1, [r2, #0]
    LDR r1, [r0, #4]
    STR r1, [r2, #4]
    LDR r1, [r0, #8]
    STR r1, [r2, #8]
    LDR r1, [r0, #12]
    STR r1, [r2, #12]
    # restore r4-r11
    LDR r4, [r0, #16]
    LDR r5, [r0, #20]
    LDR r6, [r0, #24]
    LDR r7, [r0, #28]
    LDR r8, [r0, #32]
    LDR r9, [r0, #36]
    LDR r10, [r0, #40]
    LDR r11, [r0, #44]
    # restore r12, lr, sp, pc, xPSR
    LDR r1, [r0, #48]
    STR r1, [r2, #16]
    LDR r1, [r0, #52]
    STR r1, [r2, #20]
    LDR r1, [r0, #60]
    STR r1, [r2, #24]
    LDR r1, [r0, #64]
    STR r1, [r2, #28]

    # restore CONTROL register
    BX lr


    .thumb_func
enter_user_mode:
    MRS r0, CONTROL
    ORR r0, r0, #1 
    MSR CONTROL, r0
    ISB        
    BX lr



