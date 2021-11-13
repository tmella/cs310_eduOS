
#include "inter.h"
#include "process_scheduler.h"
#include "../stdlib/stdlib.h"

#ifndef KERNEL_SYSCALLS_H
#define KERNEL_SYSCALLS_H


#define SYSCALL_EXIT 1

void sys_call_handler(i_registers_t* registers) {
    switch (registers->eax) {
        case SYSCALL_EXIT:
            kill_current_process();
            break;
        default:
            print_string("ActuallY I dont know");
            break;

    }
}

#endif //KERNEL_SYSCALLS_H
