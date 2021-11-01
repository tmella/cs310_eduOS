
#include "xinter.h"

idt_ptr interrupt_descriptor_table_ptr;
idt_entry interrupt_descriptor_table[256];

void set_idt_gate(int entryNo, uint32_t address) {
    interrupt_descriptor_table[entryNo].low_offset = address & 0xFFFF;
    interrupt_descriptor_table[entryNo].selector = 0x08;
    interrupt_descriptor_table[entryNo].zero = 0;
    interrupt_descriptor_table[entryNo].flags = 0x8e;
    interrupt_descriptor_table[entryNo].high_offset = (((address) >> 16) & 0xFFFF);
}

/*
 * We have to use this instead of memset because we cannot rely on standard libraries
 */
void load_idt() {
    interrupt_descriptor_table_ptr.limit = sizeof(idt_entry) * 255;
    interrupt_descriptor_table_ptr.base  =
            (uint32_t)&interrupt_descriptor_table;
    asm volatile("lidt (%0)" : : "r" (&interrupt_descriptor_table_ptr));
}

void install_interrupt_service_routine() {
    set_idt_gate(0, (uint32_t) isr0);
    set_idt_gate(1, (uint32_t) isr1);
    set_idt_gate(2, (uint32_t) isr2);
    set_idt_gate(3, (uint32_t) isr3);
    set_idt_gate(4, (uint32_t) isr4);
    set_idt_gate(5, (uint32_t) isr5);
    set_idt_gate(6, (uint32_t) isr6);
    set_idt_gate(7, (uint32_t) isr7);
    set_idt_gate(8, (uint32_t) isr8);
    set_idt_gate(9, (uint32_t) isr9);
    set_idt_gate(10, (uint32_t) isr10);
    set_idt_gate(11, (uint32_t) isr11);
    set_idt_gate(12, (uint32_t) isr12);
    set_idt_gate(13, (uint32_t) isr13);
    set_idt_gate(14, (uint32_t) isr14);
    set_idt_gate(15, (uint32_t) isr15);
    set_idt_gate(16, (uint32_t) isr16);
    set_idt_gate(17, (uint32_t) isr17);
    set_idt_gate(18, (uint32_t) isr18);
    set_idt_gate(19, (uint32_t) isr19);
    set_idt_gate(20, (uint32_t) isr20);
    set_idt_gate(21, (uint32_t) isr21);
    set_idt_gate(22, (uint32_t) isr22);
    set_idt_gate(23, (uint32_t) isr23);
    set_idt_gate(24, (uint32_t) isr24);
    set_idt_gate(25, (uint32_t) isr25);
    set_idt_gate(26, (uint32_t) isr26);
    set_idt_gate(27, (uint32_t) isr27);
    set_idt_gate(28, (uint32_t) isr28);
    set_idt_gate(29, (uint32_t) isr29);
    set_idt_gate(30, (uint32_t) isr30);
    set_idt_gate(31, (uint32_t) isr31);

    load_idt();
}

void isr_handler(i_registers_t registers) {
    print_string("Received interrupt: ", 0x0f);
    switch (registers.int_no) {
        case 1:
            print_string("Division by 0",0x0f);
            break;
        case 2:
            print_string("Single step interrupt",0x0f);
            break;
        case 3:
            print_string("Non maskable interrupt",0x0f);
            break;
        case 4:
            print_string("Breakpoint",0x0f);
            break;
        case 5:
            print_string("Overflow",0x0f);
            break;
        case 6:
            print_string("Bound range exceeded",0x0f);
            break;
        case 7:
            print_string("Invalid op code",0x0f);
            break;
        case 8:
            print_string("Division by 0",0x0f);
            break;
        case 9:
            print_string("Division by 0",0x0f);
            break;
        case 10:
            print_string("Division by 0",0x0f);
            break;
        case 11:
            print_string("Division by 0",0x0f);
            break;
        case 12:
            print_string("Division by 0",0x0f);
            break;
        case 13:
            print_string("Division by 0",0x0f);
            break;
        case 14:
            print_string("Division by 0",0x0f);
            break;
        case 15:
            print_string("Division by 0",0x0f);
            break;
        case 16:
            print_string("Division by 0",0x0f);
            break;
        case 17:
            print_string("Division by 0",0x0f);
            break;
        case 18:
            print_string("Division by 0",0x0f);
            break;
        case 19:
            print_string("Division by 0",0x0f);
            break;
        case 20:
            print_string("Division by 0",0x0f);
            break;
        case 21:
            print_string("Division by 0",0x0f);
            break;
        case 22:
            print_string("Division by 0",0x0f);
            break;
        case 23:
            print_string("Division by 0",0x0f);
            break;
        case 24:
            print_string("Division by 0",0x0f);
            break;
        case 25:
            print_string("Division by 0",0x0f);
            break;
        case 26:
            print_string("Division by 0",0x0f);
            break;
        case 27:
            print_string("Division by 0",0x0f);
            break;
        case 28:
            print_string("Division by 0",0x0f);
            break;
        case 29:
            print_string("Division by 0",0x0f);
            break;
        case 30:
            print_string("Division by 0",0x0f);
            break;
        case 31:
            print_string("Reserved",0x0f);
            break;
        
    }

}
