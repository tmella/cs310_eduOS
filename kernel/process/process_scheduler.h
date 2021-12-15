
#ifndef CSWK_KERNEL_PROCESS_SCHEDULER_H
#define CSWK_KERNEL_PROCESS_SCHEDULER_H



void init_process_scheduler();

void create_process(void (*text)());
void reschedule();




#endif //CSWK_KERNEL_PROCESS_SCHEDULER_H
