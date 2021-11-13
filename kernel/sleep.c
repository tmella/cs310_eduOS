//
// Created by University  on 13/11/21.
//


#include "sleep.h"
#include "interrupts/timer.h"
#include "process_scheduler.h"

void k_sleep(unsigned int millis) {
    timer_wait(millis);


    sleep_current_process();



}
