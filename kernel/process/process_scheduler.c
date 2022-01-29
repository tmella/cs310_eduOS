
#include "process.h"
#include "../kstdlib.h"
#include "process_scheduler.h"
#include "../memory/heap.h"
#include "../memory/frame_allocator.h"
#include "../../stdlib/queue.h"
#include "../../stdlib/list.h"
#include "../../stdlib/memory.h"

#include "../interrupt/timer.h"
#include "../interrupt/irq.h"

#include "../file-system/file-system.h"

#include "../../stdlib/stdtypes.h"

#define push_to_stack(esp, elem) (*(--esp) = elem)

#define BURST_PERIOD 2000

// TODO: remember for now no processes are deleted

char scheduler_started = 0;

extern context_switch(process_control_block
*);
extern void jump_usermode(uint32_t);

unsigned int process_id;

typedef List ProcessList;
typedef Queue ProcessQueue;

ProcessQueue *ready_queue;
ProcessList *waiting_list;
ProcessList *terminated_list;

struct waiting_pcb {
  uint32_t ticks;
  process_control_block *pcb;
};

uint64_t current_running_count;
process_control_block *current;

// Keep the Idle process separate from queueing logic (avoid push/pull)
process_control_block *idle_pcb;

/* Simple helper method */
process_control_block *init_pcb() {
    return (process_control_block *) k_malloc(sizeof(process_control_block));
}

void draw_green_square() {
    // Prints a small green block
    print_free_char(' ', 76, 1, GREEN_ON_BLACK);
    print_free_char(' ', 77, 1, GREEN_ON_BLACK);
}

void clear_green_square() {
    // Prints a small green block
    clear_at(76, 1);
    clear_at(77, 1);
}

void print_bench_mark() {
    if(waiting_list->size == 0 && ready_queue->size == 0) {
        list_elem *search = terminated_list->head;
        kprintf("BENCHMARKS:");
        for(int i = 0; i < terminated_list->size; i++) {
            process_control_block * pcb = (process_control_block *) search->value;
            kprintf("\n\t Process %d ran for %ds had to wait for %ds",
                    pcb->process_id,
                    TICKS_TO_SECONDS(pcb->cpu_ticks),
                    TICKS_TO_SECONDS(pcb->waiting_ticks));
            search = search->next;
        }
    }
}

/* Idle process which puts the processor to sleep */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void idle_process_m() {
    while(1) {
        // WHY DO WE NEED TO DISABLE AND ENABLE HTL
        draw_green_square();
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
    for(int i = 0; i < 4; i++)
        push_to_stack(esp, 0);

    idle_pcb->esp = esp;
    // TODO this could be wrong as we need to access mem (check)
    idle_pcb->cr3 = 0x300000;
}

void init_process_scheduler() {
    // Init a queue that stores PCBs
    ready_queue = init_queue(sizeof(process_control_block));
    waiting_list = init_list(sizeof(struct waiting_pcb));
    terminated_list = init_list(sizeof(process_control_block));

    init_idle_process();
}

uint32_t next_pid() {
    return ++process_id;
}

int IRQ_disable_counter = 0;

void lock_scheduler(void) {
    asm volatile("cli");
    IRQ_disable_counter++;
}

void unlock_scheduler(void) {
    IRQ_disable_counter--;
    if(IRQ_disable_counter == 0) {
        asm volatile("sti");
    }
}

void start_up_process() {
    unlock_scheduler();
}

void user_start_up(uint32_t text) {
    unlock_scheduler();
    jump_usermode(text);
}

// TODO: perhaps make cleaner
process_control_block *create_process_u(char *name) {
    bin_node *file = find_file(name);

    if(!file)
        return null_ptr;

    process_control_block * pcb = init_pcb();

    page_directory_t *dir = create_kmapped_table();

    uint32_t *program_txt = alloc_frame_addr();
    memcpy(file->data, program_txt, file->size);
    map_page(dir, (unsigned int *)PROCESS_START, program_txt, 1, 1, 1);

    uint32_t stack_btm = (uint32_t) alloc_frame_addr();
    unsigned int *esp = stack_btm + FRAME_SIZE;
    push_to_stack(esp,  PROCESS_START);
    push_to_stack(esp, 0);
    push_to_stack(esp, (unsigned int) user_start_up);
    for(int i = 0; i < 4; i++)
        push_to_stack(esp, 0);
    int stack_diff = (uint32_t) esp - stack_btm;

    map_page(dir, PROCESS_STACK, stack_btm, 1, 1, 1 );

    pcb->esp = PROCESS_STACK + stack_diff;
    pcb->cr3 = dir;
    pcb->cpu_ticks = 0;
    pcb->waiting_ticks = get_current_count();
    pcb->process_id = process_id++;

    enqueue(ready_queue, pcb);

    return pcb;
}

/* What does create process do:
 *      1. Will assign the next PID
 *      2. Will add the PCB to the Process queue
 * */
process_control_block *create_process(void (*text)()) {
    process_control_block * pcb = init_pcb();

    uint32_t stack_btm = (uint32_t) alloc_frame_addr();
    unsigned int *esp = stack_btm + FRAME_SIZE;
    push_to_stack(esp, (unsigned int) text);
    push_to_stack(esp, (unsigned int) start_up_process);
    for(int i = 0; i < 4; i++)
        push_to_stack(esp, 0);
    // This value is the distance between the bottom of the stack and the data added
    int stack_diff = (uint32_t) esp - stack_btm;

    page_directory_t *dir = create_kmapped_table();

    // Map the process stack to a fixed location in mem
    map_page(dir, PROCESS_STACK, stack_btm, 1, 1, 1);

    map_page(dir, dir, dir, 1, 1, 1);

    pcb->esp = PROCESS_STACK + stack_diff;
    pcb->cr3 = dir;
    pcb->cpu_ticks = 0;
    pcb->waiting_ticks = get_current_count();
    pcb->process_id = process_id++;

    enqueue(ready_queue, pcb);

    return pcb;
}

// For now we will save the state of terminated processes
void save_current_process(unsigned int esp) {
    lock_scheduler();
    if(current) {
        current->esp = esp;
        if(current->state == RUNNING_STATE) {
            current->cpu_ticks += get_current_count() - current_running_count;
        }
    }
    unlock_scheduler();
}

void reschedule() {
    // Avoid any unnecessary context switching
    if(ready_queue->size == 0) {
        if(current->state == RUNNING_STATE) {
            return;
        }
        context_switch(idle_pcb);
    } else {
        clear_green_square();
        process_control_block * new_process =
            (process_control_block *) dequeue(ready_queue);

        if(current == new_process) {
            return;
        }

        if(new_process) {
            context_switch(new_process);
        } else {
            kprintf("PANIC: FETCHED A NULL PROCESS");
            context_switch(idle_pcb);
            // FIXME
        }
    }
}

// Entry point
void start_scheduler() {
    scheduler_started = 1;
    reschedule();
}

void set_process_running() {
    lock_scheduler();
    current_running_count = get_current_count();
    current->state = RUNNING_STATE;
    unlock_scheduler();
}

void kill_current_process(void) {
    lock_scheduler();
    current->state = TERMINATED_STATE;
    current->cpu_ticks += get_current_count() - current_running_count;
    current->waiting_ticks = get_current_count() - current->waiting_ticks;
    add_back(terminated_list, current);

//    print_bench_mark();

    reschedule();
    unlock_scheduler();
}

void wake_up_process() {
    lock_scheduler();
    if(current != idle_pcb && current->state == RUNNING_STATE) {
        enqueue(ready_queue, current);
    }
    ack_interrupt_pic();
    reschedule();
    unlock_scheduler();
}

void process_waiting() {
    if(waiting_list->size == 0) {
        return;
    }

    int index = 0;
    list_elem *iter = waiting_list->head;
    while(iter) {
        struct waiting_pcb *value = (struct waiting_pcb *) iter->value;
        value->ticks--;
        if(!value->ticks) {
            enqueue(ready_queue, value->pcb);
            remove_at(waiting_list, index);
            wake_up_process();
            break;
        }
        index++;
        iter = iter->next;
    }
}

// TODO use this to keep track of time passing
uint64_t timer_counter;

void preempt_processes() {
    // TODO: implement logic for RR scheduler
    // should safely call reschedule() every 2s
}

void scheduler_timer_handler() {
    if(scheduler_started) {
        lock_scheduler();
        process_waiting();
        preempt_processes();
        unlock_scheduler();
    }
}

void sleep_current_process(uint32_t millis) {
    lock_scheduler();
    current->cpu_ticks += get_current_count() - current_running_count;
    current->state = WAITING_STATE;

    struct waiting_pcb *waiting = k_malloc(sizeof(struct waiting_pcb));
    waiting->pcb = current;
    waiting->ticks = MILLIS_TO_TICKS(millis);

    add_back(waiting_list, waiting);

    reschedule();
    unlock_scheduler();
}
