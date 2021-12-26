
#ifndef CSWK_KERNEL_PROCESS_SCHEDULER_H
#define CSWK_KERNEL_PROCESS_SCHEDULER_H

#include "process.h"

void reschedule();
void start_scheduler();
void init_process_scheduler();

process_control_block *create_process(void (*text)());

void kill_current_process();
void set_process_running();




#endif //CSWK_KERNEL_PROCESS_SCHEDULER_H
