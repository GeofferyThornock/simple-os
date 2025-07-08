#include <kernel/idt.h>
#include <stdint.h>

void exception_handler(){
    __asm__ volatile ("cli; hlt");
}


void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags){
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low     = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs   = 0x00;
    descriptor->attributes  = flags;
    descriptor->isr_high    = (uint32_t)isr >> 16;
    descriptor->reserved    = 0;
}

void idt_init(){
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x9A);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");
};



