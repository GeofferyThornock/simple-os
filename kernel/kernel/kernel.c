#include <stdio.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
 

void kernel_main(void) {
    gdt_init();
    idt_init();
    extern void test1();

	terminal_initialize();

    printf("This is a test of the printf function\n");
}

