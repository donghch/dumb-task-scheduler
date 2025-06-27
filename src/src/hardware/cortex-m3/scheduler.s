
    .syntax unified
    .cpu cortex-m3
    .thumb
    .extern current_task
    .global scheduler_load_task
    .type scheduler_load_task, %function
    .section .text
/**
    Platform specific scheduler functions for Cortex-M3.
*/

    .thumb_func
/**
    Load the task pointer and start the task.
    This function only get called when starting the scheduler. 
    It setup PSP and PC and jump to it.
    r0 will be stack pointer, r1 will be task pointer.
    Assume the program is in priviledge mode.
 */  
scheduler_load_task:
    MSR psp, r0
    MOV r0, #3
    MSR control, r0
    ISB
    BX r1