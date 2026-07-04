ENTRY(_start)

SECTIONS {
    . = 0xffffffff80000000;

    .text : ALIGN(0x1000) {
        *(.text*)
    }

    .rodata : ALIGN(0x1000) {
        *(.rodata*)
    }

    /* Limine protocol request sections */
    .limine_requests_start : ALIGN(0x1000) {
        KEEP(*(.limine_requests_start))
    }

    .limine_requests : {
        KEEP(*(.limine_requests))
    }

    .limine_requests_end : {
        KEEP(*(.limine_requests_end))
    }

    .data : ALIGN(0x1000) {
        *(.data*)
    }

    .bss : ALIGN(0x1000) {
        *(.bss*)
        *(COMMON)
    }
}
