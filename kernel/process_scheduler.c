
#include "process_scheduler.h"
#include "process.h"
#include "../drivers/screen.h"

#include "../stdlib/stdlib.h"

#include "memory/heap.h"

unsigned int processId = 0;

ProcessQueue readyQueue;
ProcessQueue waitingQueue;

PCB *currentProcess;

void run_process(PCB* pcb) {
    pcb->text();
}

unsigned int next_pid(){
    return ++processId;
}

// TODO need to finish
PCB *create_idle_process() {
    PCB *newProcess;

    newProcess = kmalloc(sizeof(PCB));

    newProcess->pid = next_pid();

    return newProcess;
}

void init_process_scheduler(){
    init_queue(&readyQueue, 256);
    init_queue(&waitingQueue, 256);

//    currentProcess = create_idle_process();
}

void initialize_registers(struct x86_registers *reg) {
    // Initialize general purpose registers
    reg->edi = 0;
    reg->esi = 0;
    reg->ebx = 0;
    reg->edx = 0;
    reg->ecx = 0;
    reg->eax = 0;

    // Initialize segment registers
    reg->cs = 0x8; // This is the location of user code
    reg->ds = 0x10; // 0x10 is the location of user data
    reg->ss = 0x10;
    reg->es = 0x10;
    reg->fs = 0x10;
    reg->gs = 0x10;

    reg->esp = 0x12FFC; // Start at the end of memory. Remember it grows down
    reg->ebp = 0; // TODO check what this should be

    reg->eip = 0x8;

    reg->eflags = 1 << 9; // Perhaps this should also be a struct so that ist more readably
}

void createProcess(void (*text)()) {
    PCB newProcess = {
        .pid = next_pid(),
        .state = READY_STATE,
        .text = text
    };

    char val[10];
    print_string("\nCreated process with ID: ");
    print_string(itoa(newProcess.pid, val, 10));


    initialize_registers(&newProcess.registers);

    enqueue(&readyQueue, newProcess);
}

void context_switch(uint32_t newPid);

void reload_process(PCB *process) {
//
//    char val[50];
//    print_string("The esp value is ");
//    print_string(itoa(process->registers.ds, val, 16));
//
//    asm("push %0;"
//        "pop %%esp;"
//        "push %1;"
//        "push %2;"
//        "push %3;"
//    : : "g" (process->registers.esp), "g" (process->registers.eflags), "g" (process->registers.cs),
//    "g" (process->registers.eip)
//    );
//    print_string("Done first push");
//    asm("push %0;"
//        "push %1;"
//        "push %2;"
//        "push %3;"
//    : :  "g" (process->registers.ds), "g" (process->registers.es), "g" (process->registers.fs),
//    "g" (process->registers.gs)
//    );
//    print_string("Done second push");
//    asm("push %0;"
//        "push %1;"
//        "push %2;"
//        "push %3;"
//        "push %4;"
//        "push %5;"
//        "push %6;"
//        "push %7;"
//    : : "g" (process->registers.eax), "g" (process->registers.ecx), "g" (process->registers.edx),
//    "g" (process->registers.ebx), "g" (process->registers.esp), "g" (process->registers.ebp),
//    "g" (process->registers.esi), "g" (process->registers.edi)
//    );
//
//    print_string("Done third push");
//
//    asm("popa;"
//        "pop %%gs;"
//        "pop %%fs;"
//        "pop %%es;"
//        "pop %%ds;"
//        "iret;"
//        : :
//        );
//    print_string("Done this");
}

void reschedule() {
    PCB *nextProcess;
    while(1) {
        if(isEmpty(&readyQueue)) {
            print_string("There are no more processes in the queue");
            break;
        }
        nextProcess = dequeue(&readyQueue);
        if(nextProcess){
            break;
        }
    }

    nextProcess->state = RUNNING_STATE;

    reload_process(nextProcess);
    print_string("Have reloaded process");
    currentProcess = nextProcess;

    run_process(currentProcess);
}

void start_processes() {
    reschedule();
}



void kill_process(unsigned int pid) {
    print_string("Killing process\n");
    // Set to done
    currentProcess->state = TERMINATED_STATE;

    // TODO: no done list yet
    // We dont expect to revive this process ever

    // TODO: need to free mem when implemented

    // Will set the new current
    reschedule();
}

void kill_current_process() {
    kill_process(currentProcess->pid);
}


void sleep_current_process() {
    print_string("I should really sleep the current process");
}
