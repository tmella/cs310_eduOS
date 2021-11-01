
#ifndef CSWK_XINTER_H
#define CSWK_XINTER_H

#include <stdint.h>
#include "../drivers/screen.h"

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// Revisar si es valido, different resources use different registers
// This is the one with the most, check if we need them all
typedef struct {
    // data segment selector
    uint32_t ds;
    // general purpose registers pushed by pusha
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    // pushed by isr procedure
    uint32_t int_no, err_code;
    // pushed by CPU automatically
    uint32_t eip, cs, eflags, useresp, ss;
} i_registers_t;

typedef struct {
    unsigned short low_offset; // Low 2 bytes of interrupt handler offset
    unsigned short selector; // A code segment selector in the GDT
    unsigned char zero; // Zero - unused
    unsigned char flags; // Type and attributes of the descriptor
    unsigned short high_offset; // High 2 bytes of interrupt handler offset
} __attribute__((packed)) idt_entry;

typedef struct {
    uint16_t limit; // The size of the table
    uint32_t base; // Address of the first entry in the table
}__attribute__((packed)) idt_ptr;


void install_interrupt_service_routine();
void isr_handler(i_registers_t registers);

#endif //CSWK_XINTER_H
