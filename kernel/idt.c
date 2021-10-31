//
// Created by University  on 30/10/21.
//



#include "idt.h"

static const int mdays[] =
        { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

typedef struct {
    unsigned short low_offset; // Low 2 bytes of interrupt handler offset
    unsigned short selector; // A code segment selector in the GDT
    unsigned char zero; // Zero - unused
    unsigned char flags; // Type and attributes of the descriptor
    unsigned short high_offset; // High 2 bytes of interrupt handler offset
} __attribute__((packed)) idt_gate;

idt_gate interrupt_descriptor_table[256];


void init_interrupt_descriptor_table() {

    for(int i = 0; i< 256 ; i++) {
        interrupt_descriptor_table[i].low_offset;
    }
}