
#include "syscalls.h"
#include "process/process_scheduler.h"
#include "kstdlib.h"
#include "../drivers/screen.h"

extern process_control_block *first;
extern process_control_block *second;

extern context_switch(process_control_block *pcb);

int i = 1;

void handle_syscall(i_registers_t *regs) {
    char *text;
    switch (regs->eax) {
        case SYSCALL_PROCESS_EXIT:
            kill_current_process();
            break;
        case SYSCALL_PROCESS_SLEEP:
            sleep_current_process(regs->edi);
            break;
        case SYSCALL_PRINT:
             text = regs->edi;
            kprintf("The pointer is %p", text);
            print_string("This is the string : ");
            print_string(text);
            print_string("  Done with the string ");
            print_string_colour(text, regs->esi);
            break;
        default: {
            kprintf("\nUnrecognised system call %d", regs->eax);
        }
    }
}

