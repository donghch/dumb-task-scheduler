OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
FLASH_SIZE = 0x10000;
BOOTLOADER_SIZE = 0x1000;
NVM_SIZE = 0x1000;
RAM_SIZE = 0x1000;

STACK_SIZE = 0x0f00;

MEMORY {
    FLASH(rx) : ORIGIN = 0x00000000, LENGTH = 128K
    SRAM(rwx) : ORIGIN = 0x20000000, LENGTH = 8K
};

SECTIONS {

    . = ORIGIN(FLASH);
    .isr_vector ALIGN(4) : {
        KEEP(*(.isr_vector))
        KEEP(*(.isr_vector*))
    } > FLASH
    
    __stacktop__ = ORIGIN(SRAM) + LENGTH(SRAM);
    __data_load__ = LOADADDR(.data);
    . = ORIGIN(SRAM);

    .data ALIGN(4) : {
        __data_start__ = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        __data_end__ = .;
    } >SRAM AT >FLASH

    .bss ALIGN(4) (NOLOAD) : {
        __bss_start__ = .;
        *(.bss)
        *(.bss*)
        . = ALIGN(4);
        __bss_end__ = .;
        *(.noinit)
        *(.noinit*)
    } >SRAM

    . = ALIGN(4);
    __heap_start__ = .;
}

SECTIONS {
    . = ORIGIN(FLASH);
    .text : {
        KEEP(*(.stack))
        KEEP(*(.vectors))
        KEEP(*(.vectors*))
        KEEP(*(.text))
        . = ALIGN(4);
        *(.text*)
        . = ALIGN(4);
        KEEP(*(.rodata))
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH

    .preinit_array ALIGN(4): {
        __preinit_array_start__ = .;
        KEEP(*(.preinit_array))
        __preinit_array_end__ = .;
    } >FLASH

    .init_array ALIGN(4): {
        __init_array_start__ = .;
        KEEP(*(.init_array))
        __init_array_end__ = .;
    } >FLASH

    .fini_array ALIGN(4): {
        __fini_array_start__ = .;
        KEEP(*(.fini_array))
        __fini_array_end__ = .;
    } >FLASH
}