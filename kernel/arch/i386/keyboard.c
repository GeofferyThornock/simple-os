#include <kernel/isr.h>
#include <kernel/pic.h>
#include <kernel/io.h>
#include <stdio.h>
#include <kernel/keyboard.h>



void keyboard_callback(){
    int k = inb(0x60);
    printf("Keyboard Output Recieved: ");
    print_hex(k);
    
    PIC_sendEOI(IRQ1);
}


void init_kb(){
    register_interrupt_handler(IRQ1, &keyboard_callback);
}





