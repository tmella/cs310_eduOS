
#include "include/task2.h"
// OS stdlib headers
#include "syscall.h"
#include "stdlib.h"

/* Pointers to each process to be able to switch. Set in Kernel main*/
process_control_block *process_one;
process_control_block *process_two;


// TODO add helpful comment
extern void context_switch(process_control_block *pcb);

void process_one_text() {
    // TODO: add a loop, which modifies and prints a var then switch to process_two
    // Terminates the process
    exit(0);
}

void process_two_text() {
    // TODO: add a loop, which modifies and prints a var then switch to process_one
    // Terminates the process
    exit(0);
}
