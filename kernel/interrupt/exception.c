
#include "exception.h"

#include "../process/process_scheduler.h"
#include "../kstdlib.h"
#include "../kpanic.h"

extern process_control_block *current;

void general_protection_fault_handler(i_registers_t *regs) {
    kprintf("\nGeneral Protection Fault!!");
    // Reschedule if caused by a Process
    if(current) {
        kprintf(" Terminating process %d \n", current->process_id);
        kill_current_process();
    } else {
        register_dump(regs);
        PANIC("Occured in Kernel cannot recover");
    }
}
