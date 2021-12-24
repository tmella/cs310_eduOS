
#include "process.h"
#include "process_scheduler.h"
#include "../memory/heap.h"
#include "../memory/frame_allocator.h"
#include "../../stdlib/stdlib.h"

#include "../../drivers/screen.h"

#define push_to_stack(esp, elem) (*(--esp) = elem)

unsigned int process_id;

process_control_block *current;

void init_process_scheduler() {
    // TODO here we initialise queues but removed for now
}

uint32_t next_pid() {
    return ++process_id;
}

/* Extract the current value of CR3 */
uint32_t get_current_pd() {
    int cr3_value;
    asm volatile("mov %%cr3, %0" : "=r" (cr3_value));
    return cr3_value;
}

/* What does create process do:
 *      1. Will assign the next PID
 *      2. Will add the PCB to the Process queue
 * */
process_control_block *create_process(void (*text)()) {
    process_control_block *pcb = (process_control_block *) k_malloc(sizeof(process_control_block));

    unsigned int *esp = ((next_pid() + 2) * 0x100 ) << 12;
    push_to_stack(esp, (unsigned int)text);
    for(int i = 0; i  < 4; i++)
        push_to_stack(esp, 0);

    pcb->esp = esp;
    pcb->cr3 = get_current_pd();

    return pcb;
}

void save_current_process(unsigned int esp) {
    if(current) {
        current->esp = esp;
    }
}


// NOT USING FOR NOW AS TESTING WITHOUT LIST FOR DEBUGGING
//void reschedule() {
//    if (queue->size == 0) {
//        print_string("No rescheduling");
//        return;
//    } else {
//        print_string("\nIts not empty");
//    }
//
//    process_control_block *PCB = k_malloc(sizeof(process_control_block));
//
//    if(PCB) {
//        char val[10];
//        print_string("\nFound a process with ID ");
//        print_string(itoa(PCB->pid, val, 10));
//    }
//    else
//        print_string("\nDequeued something null\n");
//}



