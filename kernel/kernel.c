
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "interrupt.h"
#include "../stdlib/stdlib.h"

#include "memory/frame_allocator.h"
#include "memory/paging.h"

void main () {
    clearScreen();
    print_new_line();
    print_string("Enabling service routine... ");
    install_interrupt_service_routine();
    asm volatile("sti");
    print_string("Done successfully\n");

    print_string("\nInitialising keyboard ... ");
    initialise_keyboard();
    print_string("Done successfully\n");

    print_string("\nInitialising memory... ");
    init_mem();
    init_paging();
    print_string("Done successfully\n");


    while(1){}
}