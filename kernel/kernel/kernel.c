#include <stdio.h>
#include <kernel/tty.h>


void kernel_main(void) {
	terminal_initialize();
    char test[] = "string part of print f\n";
    printf("This is a test of the printf function\n");
    printf("%s", test);
    printf("%c", 'f');
}

