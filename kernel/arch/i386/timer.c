#include <kernel/timer.h>
#include <kernel/isr.h>
#include <stdint.h>
#include <stdio.h>

uint32_t tick = 0;

static void timer_callback(registers_t regs){
    tick++;
    char* str;
    itoa(tick, str, 16);
    puts(str);
}


