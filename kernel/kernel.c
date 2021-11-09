
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "inter.h"
#include "exit.h"

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
    print_string("Ole que funciona!!! \n"
                 "This also works\n");

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

    uint32_t n =  10;
    char *ptr = (char *) kmalloc(n * sizeof(int));
//    for (int i = 0; i < n; ++i) {
//        ptr[i] = 'a' + i; // shorthand for *(ptr + i)
//    }

    char *pt = (char *) kmalloc(n * sizeof(long long));

    print_string(ptr);

    kfree(ptr);

    kmalloc(12);

}

