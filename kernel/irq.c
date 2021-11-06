
#include "irq.h"

// TODO need to add comment per ICW
void reprogram_pic() {
    // 0x11 is the initialize command
    port_byte_out(PIC_MATER_PORT, 0x11);
    port_byte_out(PIC_SLAVE_PORT, 0x11);

    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);

    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);

    // Unmask
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);
}


/*
 * An EOI signal must be sent so that
 * we can receive further interrupts
 */
void end_of_interrupt_pic(int interruptNo) {
    // perhaps add sanity check

    port_byte_out(0x20, 0x20);
    if (interruptNo >= 0x28) // 44
        port_byte_out(0xa0, 0x20);
}

