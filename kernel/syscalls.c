
#include "syscalls.h"
#include "process/process_scheduler.h"

#include "../drivers/screen.h"

extern process_control_block *first;
extern process_control_block *second;

extern context_switch(process_control_block *pcb);

int i = 1;

void handle_syscall(i_registers_t *regs) {
    switch (regs->eax) {
        case SYSCALL_PROCESS_EXIT:
            kill_current_process();
            break;
        case SYSCALL_PROCESS_SLEEP:
            sleep_current_process(regs->edi);
            break;
        case SYSCALL_PRINT:
            print_string_colour((char *)regs->edi, regs->esi);
            break;
        default: {
//            printf("Unrecognised system call %d", regs->eax);
        }
    }
}

