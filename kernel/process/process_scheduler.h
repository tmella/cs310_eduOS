
#ifndef CSWK_KERNEL_PROCESS_SCHEDULER_H
#define CSWK_KERNEL_PROCESS_SCHEDULER_H

#include "process.h"

void init_process_scheduler();

process_control_block *create_process(void (*text)());
void reschedule();




#endif //CSWK_KERNEL_PROCESS_SCHEDULER_H
