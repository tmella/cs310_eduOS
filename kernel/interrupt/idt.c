
#include "idt.h"
#include "irq.h"
#include "../memory/paging.h"
#include "../syscalls.h"
#include "../../drivers/screen.h"
#include "../kstdlib.h"

#include "exception.h"

idt_ptr interrupt_descriptor_table_ptr;
idt_entry interrupt_descriptor_table[256];

handler interrupt_handlers[256];


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
    interrupt_descriptor_table_ptr.base =
        (uint32_t) & interrupt_descriptor_table;
    asm volatile("lidt (%0)" : : "r" (&interrupt_descriptor_table_ptr));
}

// TODO: need to check if should use gates or traps?

// More generic methods for both interrupts and traps
void set_idt_entry(uint16_t entry_n, uint32_t address, uint8_t selector, uint8_t flags) {
    interrupt_descriptor_table[entry_n].low_offset = address & 0xFFFF;
    interrupt_descriptor_table[entry_n].selector = selector;
    interrupt_descriptor_table[entry_n].zero = 0;
    interrupt_descriptor_table[entry_n].flags = flags;
    interrupt_descriptor_table[entry_n].high_offset = (((address) >> 16) & 0xFFFF);
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

    // TODO: should they be traps or gates
    set_idt_gate(32, (uint32_t) irq0);
    set_idt_gate(33, (uint32_t) irq1);
    set_idt_gate(34, (uint32_t) irq2);
    set_idt_gate(35, (uint32_t) irq3);
    set_idt_gate(36, (uint32_t) irq4);
    set_idt_gate(37, (uint32_t) irq5);
    set_idt_gate(38, (uint32_t) irq6);
    set_idt_gate(39, (uint32_t) irq7);
    set_idt_gate(40, (uint32_t) irq8);
    set_idt_gate(41, (uint32_t) irq9);
    set_idt_gate(42, (uint32_t) irq10);
    set_idt_gate(43, (uint32_t) irq11);
    set_idt_gate(44, (uint32_t) irq12);
    set_idt_gate(45, (uint32_t) irq13);
    set_idt_gate(46, (uint32_t) irq14);
    set_idt_gate(47, (uint32_t) irq15);

    // Set gate for system calls
    set_idt_entry(128, (uint32_t) isr80, 0x08, DPL3_INTERRUPT);

    reprogram_pic();

    load_idt();
}

void add_handler(int num, handler handlerFunc) {
    // TODO add sanity check
    interrupt_handlers[num] = handlerFunc;
}

void irq_handler(i_registers_t *reg) {
    if (interrupt_handlers[reg->int_no] != 0) {
        handler func = interrupt_handlers[reg->int_no];
        func(reg);
    }
    ack_interrupt_pic();
}

/*
 * For a detailed explanation of each type of exception (interrupt from 1-30)
 *  please refer to the following page:  https://wiki.osdev.org/Exceptions
 */
void isr_handler(i_registers_t *registers) {
    // Switch statement
    switch (registers->int_no) {
        case 1:
            print_string("Division by 0");
            break;
        case 2:
            print_string("Single step interrupt");
            break;
        case 3:
            print_string("Non maskable interrupt");
            break;
        case 4:
            print_string("Breakpoint");
            break;
        case 5:
            print_string("Overflow");
            break;
        case 6:
            kprintf("Bound range exceeded %p", registers->eip);
            break;
        case 7:
            print_string("Invalid op code");
            break;
        case 8:
            print_string("Double fault");
            break;
        case 9:
            print_string("Coprocessor Segment Overrun");
            break;
        case 10:
            print_string("Invalid TSS");
            break;
        case 11:
            print_string("Segment Not Present");
            break;
        case 12:
            print_string("Stack-Segment Fault");
            break;
        case 13:
            general_protection_fault_handler(registers);
            break;
        case 14:
            page_fault_handler(registers);
            break;
        case 15:
            print_string("Reserved 15");
            break;
        case 16:
            // Is this possible on i386 arch? check
            print_string("x87 Floating Point Exception");
            break;
        case 17:
            print_string("Alignment Check");
            break;
        case 18:
            print_string("Machine Check");
            break;
        case 19:
            print_string("SIMD Floating-Point Exception");
            break;
        case 20:
            print_string("Virtualization Exception");
            break;
        case 21:
            print_string("Control Protection Exception");
            break;
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
            kprintf("Reserved %d", registers->int_no);
            break;
        case 28:
            print_string("Hypervisor Injection Exception");
            break;
        case 29:
            print_string("VMM Communication Exception");
            break;
        case 30:
            print_string("Security Exception");
            break;
        case 31:
            print_string("Reserved");
            break;
            // System calls
        case 80:
            handle_syscall(registers);
            break;
    }
}

void register_dump(i_registers_t *regs) {
    kprintf("\nDS: 0x%p", regs->ds);
    kprintf("\nEDI: %p, ESI: %p, EBP: %p", regs->edi, regs->esi, regs->ebp);
    kprintf("\nESP: %p, EBX: %p, EDX: %p", regs->esp, regs->ebx, regs->edx);
    kprintf("\nECX: %p, EAX: %p", regs->ecx, regs->eax);
    kprintf("\nInterrupt Number: %d Error Code: %p", regs->int_no, regs->err_code);
    kprintf("\nEIP: %p, CS: 0x%p, EFLAGS: %p, u_esp: %p, ss: %p",
           regs->eip,
           regs->cs,
           regs->eflags,
           regs->useresp,
           regs->ss);
}
