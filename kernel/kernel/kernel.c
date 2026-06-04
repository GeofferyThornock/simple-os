#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <kernel/isr.h>
#include <kernel/keyboard.h>
#include <kernel/pic.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/timer.h>

extern isr_t interrupt_handlers[];

typedef struct {
        unsigned int flags;         
        unsigned int mem_lower;     
        unsigned int mem_upper;     
        unsigned int boot_device;   
        unsigned int cmdline;       
        unsigned int mods_count;    
        unsigned int mods_addr;     
        unsigned int num;          
        unsigned int size;         
        unsigned int addr;         
        unsigned int shndx;        
        unsigned int mmap_length;   
        unsigned int mmap_addr;     
} MultiBootInfo;

typedef struct {
        unsigned int size;
        unsigned int base_addr_low;
        unsigned int base_addr_high;
        unsigned int length_low;
        unsigned int length_high;
        unsigned int type;
} __attribute__((packed)) MemoryInfo;


void parse_memory_map(MultiBootInfo* info)
{
        if(!(info->flags & 0x40)) {
                printf("you're... not gonna wanna hear this");
                return;
        };

        unsigned int current = (int)info->mmap_addr;
        unsigned int end = (int)info->mmap_addr + info->mmap_length;

        while(current < end){
                MemoryInfo* memory = (MemoryInfo*)current;

                if(memory->type == 1){
                        printf("Base: ");
                        print_hex(memory->base_addr_low);
                        printf("Length: ");
                        print_hex(memory->length_low);
                        printf("Type: ");
                        print_hex(memory->type);
                }


                current = current + memory->size + 4;
        }

        print_hex(info->flags);
        print_hex((int)info->mmap_addr);
        print_hex(info->mmap_length);

        asm volatile("hlt");
}


void init_descriptors()
{
        gdt_init();
        idt_init();
        memset(&interrupt_handlers, 0, sizeof(isr_t)*256);
}


void kernel_main(int magic_number, int* ptr) 
{
        terminal_initialize();

        MultiBootInfo* info = (MultiBootInfo*)ptr;

        parse_memory_map(info);

        init_descriptors();

        asm volatile("sti");

        init_timer(50);


        init_kb();
}

