
#include "process.h"
#include "process_scheduler.h"
#include "../../stdlib/queue.h"
#include "../memory/heap.h"
#include "../memory/frame_allocator.h"
#include "../../stdlib/stdlib.h"

#include "../../drivers/screen.h"

typedef Queue ProcessQueue;

ProcessQueue *queue;
process_control_block *current_process;

unsigned int process_id;

void init_process_scheduler() {
    queue = init_queue(sizeof(process_control_block));
}

uint32_t next_pid() {
    return ++process_id;
}

/* What does create process do:
 *
 *      1. Will assign the next PID
 *      2. Will add the PCB to the Process queue
 *
 *
 *
 * */

void create_process(void (*text)()) {
    process_control_block PCB = {
        .pid = next_pid(),
        .state = READY_STATE,
        .text = text
    };

    char val[10];
    print_string("\nCreated process with ID: ");
    print_string(itoa(PCB.pid, val, 10));

    // Add to queue
    enqueue(queue, &PCB);
}

void reschedule() {
    if (queue->size == 0) {
        print_string("No rescheduling");
        return;
    } else {
        print_string("\nIts not empty");
    }

    process_control_block *PCB = k_malloc(sizeof(process_control_block));

    dequeue(queue, PCB);

    if(PCB) {
        char val[10];
        print_string("\nFound a process with ID ");
        print_string(itoa(PCB->pid, val, 10));
    }
    else
        print_string("\nDequeued something null\n");
}



