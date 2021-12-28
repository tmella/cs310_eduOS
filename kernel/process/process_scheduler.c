
#include "process.h"
#include "process_scheduler.h"
#include "../memory/heap.h"
#include "../memory/frame_allocator.h"
#include "../../stdlib/stdlib.h"
#include "../../stdlib/queue.h"
#include "../../stdlib/list.h"

#include "../interrupt/timer.h"

#define push_to_stack(esp, elem) (*(--esp) = elem)

// TODO: remember for now no processes are deleted

extern context_switch(process_control_block
*pcb);

unsigned int process_id;

typedef Queue ProcessQueue;

List *waiting_list;

struct waiting_pcb {
  uint32_t ticks;
  process_control_block *pcb;
};

process_control_block *current;

ProcessQueue *ready_queue;
// Keep the Idle process separate from queueing logic (avoid push/pull)
process_control_block *idle_process;

process_control_block *idle_pcb;

/* Simple helper method */
process_control_block *init_pcb() {
    return (process_control_block *) k_malloc(sizeof(process_control_block));
}

/* Idle process which puts the processor to sleep */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void idle_process_m() {
    printf("\nRunning the idle process\n");
    while (1) {
        // WHY DO WE NEED TO DISABLE AND ENABLE HTL
        asm volatile("sti");
        asm volatile("hlt");
        asm volatile("cli");
    }
}
#pragma clang diagnostic pop

void init_idle_process() {
    idle_pcb = init_pcb();

    unsigned int *esp = alloc_frame_addr();
    push_to_stack(esp, (unsigned int) idle_process_m);
    for (int i = 0; i < 4; i++)
        push_to_stack(esp, 0);

    idle_pcb->esp = esp;
    idle_pcb->cr3 = 0; // TODO this could be wrong
}

void init_process_scheduler() {
    // Init a queue that stores PCBs
    ready_queue = init_queue(sizeof(process_control_block));
    waiting_list = init_list(sizeof(struct waiting_pcb));

    // TODO todo need to initialise the init process
    init_idle_process();
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
    process_control_block * pcb = init_pcb();

    unsigned int *esp = alloc_frame_addr();
    push_to_stack(esp, (unsigned int) text);
    for (int i = 0; i < 4; i++)
        push_to_stack(esp, 0);

    pcb->esp = esp;
    pcb->cr3 = get_current_pd();

    enqueue(ready_queue, pcb);

    return pcb;
}

// For now we will save the state of terminated processes
void save_current_process(unsigned int esp) {
    if (current) {
        current->esp = esp;
    }
}

// NOT USING FOR NOW AS TESTING WITHOUT LIST FOR DEBUGGING
void reschedule() {
    if (ready_queue->size == 0) {
        context_switch(idle_pcb);
    } else {
        process_control_block * new_process =
            (process_control_block *) dequeue(ready_queue);

        if (new_process) {
            context_switch(new_process);
        } else {
            printf("PANIC: SHIT ITS NULL");
            context_switch(idle_process);
            // FIXME
        }
    }
}

// Entry point
void start_scheduler() {
    reschedule();
}

void set_process_running() {
    current->status = RUNNING_STATE;
}

void kill_current_process() {
    current->status = TERMINATED_STATE;
}

void unblock_waiting() {
    if (waiting_list->size == 0) {
        return;
    }

    int index = 0;
    list_elem *iter = waiting_list->head;
    while (iter) {
        struct waiting_pcb *value = (struct waiting_pcb *) iter->value;
        value->ticks--;
        if (!value->ticks) {
            printf("The number of queued elements is %d", waiting_list->size);
            printf("This has been reached!!");
            enqueue(ready_queue, value->pcb);
            remove_at(waiting_list, index);
            reschedule();
            break;
        }
        index++;
        iter = iter->next;
    }
}

void sleep_current_process(uint32_t millis) {
    current->status = WAITING_STATE;

    struct waiting_pcb *waiting = k_malloc(sizeof(struct waiting_pcb));
    waiting->pcb = current;
    waiting->ticks = millis_to_ticks(millis);

    add_back(waiting_list, waiting);
}

void add_current_back() {
    if(current) {
        enqueue(ready_queue, current);
    }
}

