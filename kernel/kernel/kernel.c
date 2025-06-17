#include <stdio.h>
#include <kernel/tty.h>


void kernel_main(void) {
	terminal_initialize();
    printf("This is a test of the printf function\n");
}

