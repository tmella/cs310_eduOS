//
// Created by University  on 3/11/21.
//

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

void runNextProcess();



#endif //CSWK_KERNEL_PROCESS_SCHEDULER_H
