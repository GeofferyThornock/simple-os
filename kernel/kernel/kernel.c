#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>

 

void kernel_main(void) {
    gdt_init();

	terminal_initialize();

    printf("This is a test of the printf function\n");
}

