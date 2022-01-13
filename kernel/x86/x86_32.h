
/*
 * This file contains basic register manipulation and fetching.
 * */

#ifndef CSWK_KERNEL_X86_X86_32_H
#define CSWK_KERNEL_X86_X86_32_H

#include <stdint.h>

uint32_t get_kstack() {
    uint32_t stack;
    asm volatile("mov %%esp, %0" : "=a"(stack));
    return stack;
}

uint64_t get_gdt_address() {
    uint64_t address;
    asm volatile ("sgdt %0":"=m"(address)::"memory");
    return address;
}



#endif //CSWK_KERNEL_X86_X86_32_H
