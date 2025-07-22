#include <stdint.h>
#define PIC1    0x20    // Master PIC
#define PIC2    0xA0    // Slave PIC
#define PIC1_COMMAND    PIC1
#define PIC1_DATA   (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA   (PIC2+1)

#define ICW1_ICW4       0x01    // Indicates the ICW4 will be present
#define ICW1_SINGLE     0x02    // Single (Cascade) Mode
#define ICW1_INTERVAL4  0x04    // Call adr 4
#define ICW1_LEVEL      0x08    // Level triggered (edge) mode
#define ICW1_INIT       0x10    // Initialization command

#define ICW4_8086       0x01
#define ICW4_AUTO       0x02
#define ICW4_BUF_SLAVE  0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM       0x10    // Special fully nested (not)

#define PIC_READ_IRR    0x0A
#define PIC_READ_ISR    0x0B

#define CASCADE_IRQ 2


#define PIC_EOI     0x20

void PIC_sendEOI(uint8_t irq);
void PIC_remap(int offset1, int offset2);
void pic_disable(void);
void IRQ_set_mask(uint8_t IRQline);
void IRQ_clear_mask(uint8_t IRQline);
static uint16_t __pic_get_irq_reg(int ocw3);
uint16_t pic_get_irr(void);
uint16_t pic_get_isr(void);

