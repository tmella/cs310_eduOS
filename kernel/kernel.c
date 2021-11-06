
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "inter.h"
#include "exit.h"

#include "process_scheduler.h"

void this_does_nothign() {
    print_string("This does nothing \n\n");

    k_exit();
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
    init_process_scheduler();

    print_new_line();

    createProcess(this_does_nothign);

    print_string("\nThis is post process creation \n");

    runNextProcess();

}

