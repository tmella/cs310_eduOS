
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "interrupt/timer.h"
#include "interrupt/idt.h"
#include "interrupt/gdt.h"
#include "kpanic.h"

#include "shell.h"
#include "memory/paging.h"
#include "memory/heap.h"
#include "memory/frame_allocator.h"

#include "process/process_scheduler.h"

#include "process/tasks/include/task1.h"
#include "process/tasks/include/task2.h"


#include "kstdlib.h"
#include "string.h"
#include "stdtypes.h"

void wait_for_understanding();

void main() {
    clear_screen();
    print_new_line();
    load_gdt();
    kprintf("Enabling service routine... ");
    install_interrupt_service_routine();
    asm volatile("sti");
    kprintf("Done successfully");

    kprintf("\nInitialising keyboard ... ");
    initialise_keyboard();
    kprintf("Done successfully");

    kprintf("\nInitialising memory... ");
    init_mem();
    init_kheap();
    init_paging();
    kprintf("Done successfully");

    init_timer();

    kprintf("\nInitialising processes ...");
    init_process_scheduler();
    kprintf("Done successfully\n");

    wait_for_understanding();

    create_kernel_process(run_shell);

    start_scheduler();

    // Should be unreachable but if reached will stop an uncontrolled crash
    PANIC("Reached end of kernel");
}


void wait_for_understanding() {
    kprintf("\n\nTake a minute to understand what is happening on startup!!\n");
    kprintf("\nPress 'y' to continue: ");

//     blocking_wait_for_char('y');
    clear_screen();
    print_new_line();
}
