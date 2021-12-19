
#ifndef CSWK_KERNEL_SYSCALLS_H
#define CSWK_KERNEL_SYSCALLS_H

#include "interrupt/idt.h"

void handle_syscall(i_registers_t* regs);

#endif //CSWK_KERNEL_SYSCALLS_H
