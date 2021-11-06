
#include "process_scheduler.h"
#include "process.h"
#include "../utils/queue.h"

#include "../stdlib/stdlib.h"

unsigned int processId = 0;

ProcessQueue jobQueue;
ProcessQueue readyQueue;
ProcessQueue deviceQueue;

PCB *currentProcess;

void init_process_scheduler(){
    init_queue(&jobQueue, 256);
}

unsigned int next_pid(){
    return ++processId;
}

void createProcess(void (*text)()) {
    PCB newProcess = {
        .pid = next_pid(),
        .state = READY_STATE,
        .text = text
    };

    char str[10];
    print_string(itoa(newProcess.pid, str, 10));

    enqueue(&jobQueue, &newProcess);
}

void runNextProcess() {
    PCB * nextProcess = dequeue(&jobQueue);

    if(nextProcess) {
        print_string("It exists you moron\n");
    } else {
        print_string("\n Its empty you twat \n");
    }

//    print_string(itoa(nextProcess->pid, str, 10));

    void (*fghj)() = nextProcess->text;

    fghj();
    fghj();

}
