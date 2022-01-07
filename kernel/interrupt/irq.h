
#ifndef CSWK_IRQ_H
#define CSWK_IRQ_H

#include "../low_level.h"

#define PIC_MATER_PORT 0x20 // Command port
#define PIC_SLAVE_PORT 0xA0 // Slave port

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void reprogram_pic();
void ack_interrupt_pic();

#endif //CSWK_IRQ_H
