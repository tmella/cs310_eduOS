
#include "syscall.h"
#include "memory.h"

int main(int argc, char *argv[]);

/* This method is called via the stack. Not through C, therefore
 * you need to be careful as we dont get much help from the compiler */
void _start(int start_ptr) {

    /* Get Argc from the call stack */
    int argc_addr = (int)&start_ptr + 0x20 + 4;
    int argc = *((int *) argc_addr);

    /* Fetch address for argv */
    char** argvs;
    if(argc > 0) {
        argvs = *((int *)argc_addr + 1);
    }

    /* Initialise the heap for this process */
    init_heap();

    /* Call exit syscall on the return value of main */
    exit(main(argc, argvs));
}