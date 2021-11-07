
#ifndef CSWK_KERNEL_PROCESS_SCHEDULER_H
#define CSWK_KERNEL_PROCESS_SCHEDULER_H

#include "process.h"
#include "../utils/queue.h"

extern ProcessQueue jobQueue;
extern ProcessQueue readyQueue;
extern ProcessQueue deviceQueue;

extern PCB *currentProcess;

void init_process_scheduler();

void createProcess(void (*text)());

void start_processes();

void context_switch(uint32_t newPid);

void kill_current_process();



#endif //CSWK_KERNEL_PROCESS_SCHEDULER_H
