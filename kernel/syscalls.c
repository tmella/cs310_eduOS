
#include "syscalls.h"
#include "process/process_scheduler.h"

#define SYSCALL_EXIT 1

void handle_syscall(i_registers_t *regs) {
    switch (regs->eax) {
        case SYSCALL_EXIT:
//            save_current_process(regs);
//            kill_current_process();
//            reschedule();
            break;
        default: {
            print_string("Unrecognised system call");
        }
    }
}

