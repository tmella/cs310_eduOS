
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "interrupt/timer.h"
#include "interrupt/idt.h"
#include "interrupt/gdt.h"


#include "memory/paging.h"
#include "memory/heap.h"
#include "memory/frame_allocator.h"

#include "process/process_scheduler.h"

#include "process/tasks/include/task1.h"
#include "process/tasks/include/task2.h"

#include "../stdlib/stdlib.h"

void wait_for_understanding();

void user_process() {
    printf("This is a process");
//    asm volatile("sti");
    while(1);
}

extern void jump_usermode(void);

void main() {
    clearScreen();
    print_new_line();
    load_gdt();
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

    process_one = create_process(process_one_text);
    process_two = create_process(process_two_text);



    // Should be unreachable but if reached will stop an uncontrolled crash
    while (1) {
        // TODO add a debug dump
    }
}


void wait_for_understanding() {
    printf("\n\nTake a minute to understand what is happening on startup!!\n");
    printf("\nPress 'y' to continue: ");

    blocking_wait_for_char('y');
    clearScreen();
    print_new_line();
}