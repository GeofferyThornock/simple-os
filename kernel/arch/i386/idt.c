#include <kernel/idt.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>

void isr_handler(registers_t regs){
    char* str = NULL;
    itoa(regs.int_no, str, 16);

    puts(str);
}


void idt_set_gate(uint8_t vector, uint32_t isr, uint8_t flags){
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low     = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs   = 0x08;
    descriptor->attributes  = flags;
    descriptor->isr_high    = (uint32_t)isr >> 16;
    descriptor->reserved    = 0;
}

void idt_init(){
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    memset(&idt, 0, sizeof(idt_entry_t)*256);

    idt_set_gate(0, (uint32_t)isr0, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x8E);
    idt_set_gate(2, (uint32_t)isr2, 0x8E);
    idt_set_gate(3, (uint32_t)isr3, 0x8E);
    idt_set_gate(4, (uint32_t)isr4, 0x8E);
    idt_set_gate(5, (uint32_t)isr5, 0x8E);
    idt_set_gate(6, (uint32_t)isr6, 0x8E);
    idt_set_gate(7, (uint32_t)isr7, 0x8E);
    idt_set_gate(8, (uint32_t)isr8, 0x8E);
    idt_set_gate(9, (uint32_t)isr9, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x8E);

    idt_set_gate(32, (uint32_t)irq0, 0x8E); // Timer
    idt_set_gate(33, (uint32_t)irq1, 0x8E); // Keyboard
    idt_set_gate(34, (uint32_t)irq2, 0x8E); // Cascade
    idt_set_gate(35, (uint32_t)irq3, 0x8E); // COM2
    idt_set_gate(36, (uint32_t)irq4, 0x8E); // COM1
    idt_set_gate(37, (uint32_t)irq5, 0x8E); // LPT2 / Sound
    idt_set_gate(38, (uint32_t)irq6, 0x8E); // Floppy
    idt_set_gate(39, (uint32_t)irq7, 0x8E); // LPT1 / Spurious
    idt_set_gate(40, (uint32_t)irq8, 0x8E); // Real-Time Clock
    idt_set_gate(41, (uint32_t)irq9, 0x8E); // ACPI / Redirected IRQ2
    idt_set_gate(42, (uint32_t)irq10, 0x8E); // Free / Network
    idt_set_gate(43, (uint32_t)irq11, 0x8E); // Free / General
    idt_set_gate(44, (uint32_t)irq12, 0x8E); // PS/2 Mouse
    idt_set_gate(45, (uint32_t)irq13, 0x8E); // FPU / Math Co-Processor
    idt_set_gate(46, (uint32_t)irq14, 0x8E); // Primary ATA Hard Disk
    idt_set_gate(47, (uint32_t)irq15, 0x8E); // Secondary ATA Hard Disk



    idt_flush((uint32_t)&idtr);
};





