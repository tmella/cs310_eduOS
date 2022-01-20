
#include "exception.h"

#include "../process/process_scheduler.h"
#include "../../stdlib/stdlib.h"

extern process_control_block *current;

void general_protection_fault_handler(i_registers_t *regs) {
    printf("\nGeneral Protection Fault!!");
    // Reschedule if caused by a Process
    if(current) {
        printf(" Terminating process %d \n", current->process_id);
        kill_current_process();
    } else {
        // ELSE PANIC
        printf(" Occurred in Kernel cannot recover.");
        register_dump(regs);
        while(1);
    }
}
