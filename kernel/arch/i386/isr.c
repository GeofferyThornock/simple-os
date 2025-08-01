#include <kernel/io.h>
#include <kernel/isr.h>
#include <stdint.h>
#include <stdio.h>

isr_t interrupt_handlers[256];

void isr_handler(registers_t regs){
    printf("Interrupt Caught: ");
    print_hex(regs.int_no);

    if(interrupt_handlers[regs.int_no] != 0){
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}
 
void irq_handler(registers_t regs){
    if(regs.int_no >= 40){
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);

    if(interrupt_handlers[regs.int_no] != 0){
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}


void register_interrupt_handler(uint8_t n, isr_t handler){
    interrupt_handlers[n] = handler;
}


