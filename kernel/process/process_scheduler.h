
#ifndef CSWK_KERNEL_PROCESS_SCHEDULER_H
#define CSWK_KERNEL_PROCESS_SCHEDULER_H

#include "process.h"

void reschedule();
void start_scheduler();
void init_process_scheduler();

process_control_block *create_user_process(char *name, int argc, char **argv);
process_control_block *create_kernel_process(void (*text)());

void kill_current_process();
void set_process_running();

void scheduler_timer_handler();

void sleep_current_process(uint32_t millis);

void local_switch(process_control_block *pcb);

void save_current_process(unsigned int esp);

void run_process(void);


#endif //CSWK_KERNEL_PROCESS_SCHEDULER_H
