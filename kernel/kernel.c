
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "inter.h"
#include "exit.h"
#include "interrupts/timer.h"
#include "memory/heap.h"

#include "process_scheduler.h"

void this_does_nothign() {
    print_string("This does nothing \n\n");

    k_exit();
}

void this_is_the_idle_process() {
    print_string("Running the idle process\n" );
}

void main () {
    clearScreen();

    install_interrupt_service_routine();

    asm volatile("sti");

    print_string("Initialising keyboard ... \n");
    initialise_keyboard();

    print_string("Initialising process scheduler ... \n");
//    init_process_scheduler();

    print_new_line();

//    createProcess(this_is_the_idle_process);
//    createProcess(this_does_nothign);

//    start_processes();

    print_string("Initializing heap ... ");
    init_heap();
    print_string( "Done successfully \n\n");

    print_string("Initializing timer ... ");
    init_timer();
    print_string( "Done successfully \n\n");


}

