
#include "syscalls.h"
#include "process/process_scheduler.h"
#include "../stdlib/stdlib.h"

extern process_control_block *first;
extern process_control_block *second;

extern context_switch(process_control_block *pcb);

int i = 1;

void handle_syscall(i_registers_t *regs) {
    switch (regs->eax) {
        case SYSCALL_PROCESS_EXIT:
            kill_current_process();
            reschedule();
            break;
        case SYSCALL_PROCESS_SLEEP:
            sleep_current_process(regs->edi);
            reschedule();
            break;
        default: {
            print_string("Unrecognised system call");
        }
    }
}

