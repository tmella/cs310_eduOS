
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "interrupt/idt.h"

#include "memory/paging.h"
#include "memory/heap.h"
#include "memory/frame_allocator.h"

#include "process/process_scheduler.h"

#include "../stdlib/stdlib.h"
#include "../stdlib/queue.h"

#include "process/process.h"

void some_function() {
    print_string("This does something\n");
}

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
    init_heap();
    init_paging();
    print_string("Done successfully\n");

    print_string("\nInitialising processes ...");
    init_process_scheduler();
    print_string("Done successfully\n");

    create_process(some_function);
    create_process(some_function);
    create_process(some_function);
    create_process(some_function);

    reschedule();
    reschedule();
    reschedule();

    char val[10];
    print_string("This is the value we are looking for ");
    print_string(itoa(0x10, val, 16));

    while(1){}

}