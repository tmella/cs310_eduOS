
#ifndef CSWK_KERNEL_INTERRUPT_EXCEPTION_H
#define CSWK_KERNEL_INTERRUPT_EXCEPTION_H

/* Exception Handlers
 * Here we will include all the handlers for exceptions.
 * */

#include "idt.h"

void general_protection_fault_handler(i_registers_t *regs);

#endif //CSWK_KERNEL_INTERRUPT_EXCEPTION_H
