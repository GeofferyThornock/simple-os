#include <kernel/timer.h>
#include <kernel/io.h>
#include <kernel/isr.h>
#include <stdint.h>
#include <stdio.h>


int tick = 0;
static void timer_callback(registers_t regs){
    tick++;
    print_dec(tick);
}

void init_timer(uint32_t frequency){
    register_interrupt_handler(IRQ0, &timer_callback);

    uint32_t divisor = 1193180 / frequency;

    outb(0x43, 0x36);

    uint8_t l = (uint8_t) (divisor & 0xFF);
    uint8_t h = (uint8_t) ((divisor>>8) & 0xFF);


    outb(0x40, l);
    outb(0x40, h);
}

