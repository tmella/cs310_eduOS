
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "interrupt/timer.h"
#include "interrupt/idt.h"

#include "memory/paging.h"
#include "memory/heap.h"
#include "memory/frame_allocator.h"

#include "process/process.h"
#include "process/process_scheduler.h"
#include "process/example_processes.h"

#include "../stdlib/exit.h"
#include "../stdlib/stdlib.h"

// FIXME: adding initial switch logic in this file
extern context_switch(process_control_block *pcb);

void first_process() {
//    int i = 0;
//    while(i < 3) {
//        printf("First pre sleep %d", i++);
//        sleep(10000);
//    }
//    printf("This is post sleep %d", i);

    printf("\nPre sleep");
    sleep(10000);
    printf("\n Post sleep");
    exit(0);
}

void second_process() {
    printf("\nThis is the second");
    sleep(50000);
    printf("Second post sleep");
    while (1);
}

void periodic_test() {
    print_string("Periodic test");
}

void wait_for_understanding() {
    printf("\n\nTake a minute to understand what is happening on startup!!\n");
    printf("\nPress 'y' to continue: ");

    blocking_wait_for_char('y');
    clearScreen();
    print_new_line();
}

void main() {
    clearScreen();
    print_new_line();
    print_string("Enabling service routine... ");
    install_interrupt_service_routine();
    asm volatile("sti");
    print_string("Done successfully");

    print_string("\nInitialising keyboard ... ");
    initialise_keyboard();
    print_string("Done successfully");

    print_string("\nInitialising memory... ");
    init_mem();
    init_heap();
    init_paging();
    print_string("Done successfully");

    init_timer();

    print_string("\nInitialising processes ...");
    init_process_scheduler();
    print_string("Done successfully\n");

    wait_for_understanding();

    create_process(welcome_process);

    create_process(first_process);
    create_process(second_process);

    reschedule();


    // Should be unreachable but if reached will stop an uncontrolled crash
    while (1) {
        // TODO add a debug dump
    }
}