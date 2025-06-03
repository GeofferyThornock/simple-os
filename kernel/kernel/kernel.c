#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	terminal_writestring("Hello, kernel World!\n");
    terminal_writestring("testing the new \n line");
}

