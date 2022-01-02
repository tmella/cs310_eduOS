
#ifndef CSWK_KERNEL_SYSCALLS_H
#define CSWK_KERNEL_SYSCALLS_H

#include "interrupt/idt.h"

#define SYSCALL_PROCESS_EXIT 0
#define SYSCALL_PROCESS_SLEEP 1

void handle_syscall(i_registers_t* regs);

#endif //CSWK_KERNEL_SYSCALLS_H
