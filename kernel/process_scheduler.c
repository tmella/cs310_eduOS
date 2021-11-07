
#include "process_scheduler.h"
#include "process.h"
#include "../drivers/screen.h"

#include "../stdlib/stdlib.h"

unsigned int processId = 0;

ProcessQueue jobQueue;
ProcessQueue readyQueue;
ProcessQueue deviceQueue;

PCB *currentProcess;

void init_process_scheduler(){
    init_queue(&readyQueue, 256);

//    currentProcess =
}

unsigned int next_pid(){
    return ++processId;
}

PCB *create_idle_process() {

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
    reg->cs = 0x80000000; // This is the location of user code
    reg->ds = 0x10000000; // 0x10 is the location of user data
    reg->ss = 0x10000000;
    reg->es = 0x10000000;
    reg->fs = 0x10000000;
    reg->gs = 0x10000000;

    reg->esp = 0xfffffff0; // Start at the end of memory. Remember it grows down
    reg->ebp = 0; // TODO check what this should be

    reg->eip = 0;

    reg->eflags = 1 << 9; // Perhaps this should also be a struct so that ist more readably
}

void createProcess(void (*text)()) {
    PCB newProcess = {
        .pid = next_pid(),
        .state = READY_STATE,
        .text = text
    };

    initialize_registers(&newProcess.registers);

    currentProcess = enqueue(&readyQueue, newProcess);
}

void context_switch(uint32_t newPid);

void kill_process(unsigned int pid) {

    char val[10];
    print_string("I want to killl the process with ID: ");
    print_string(itoa(currentProcess->pid, val, 10));
    print_string(" but it has not been implemented yet");
}

void kill_current_process() {
    kill_process(currentProcess->pid);
}


void start_processes() {
    PCB * nextProcess = dequeue(&readyQueue);

    void (*fghj)() = nextProcess->text;
    fghj();
}
