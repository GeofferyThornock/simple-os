#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <kernel/isr.h>
#include <kernel/pic.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/timer.h>

extern isr_t interrupt_handlers[];

void init_descriptors(){
    gdt_init();
    idt_init();
    memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
}
 

void kernel_main(void) {
    init_descriptors();
	terminal_initialize();
    
    asm volatile("int $0x3");
    asm volatile("int $0x4");

    asm volatile("sti");
    IRQ_set_mask(32);
    init_timer(50);
}

