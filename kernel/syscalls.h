
#include "inter.h"
#include "process_scheduler.h"
#include "../stdlib/stdlib.h"

#ifndef CSWK_KERNEL_SYSCALLS_H
#define CSWK_KERNEL_SYSCALLS_H


#define SYSCALL_EXIT 1

void sys_call_handler(i_registers_t* registers) {
    switch (registers->eax) {

        case SYSCALL_EXIT:
            print_string("This is a one");


            break;
        default:
            print_string("ActuallY I dont know");
            break;

    }
}

#endif //CSWK_KERNEL_SYSCALLS_H
