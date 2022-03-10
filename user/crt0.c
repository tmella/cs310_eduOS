
#include "syscall.h"
#include "memory.h"

int main(int argc, char *argv[]);

/* This method is called via the stack. Not through C, therefore
 * you need to be careful as we dont get much help from the compiler */
void _start(int start_ptr, char *argv[]) {

    // When we set up the stack the var will point to the top
    // So we "increment" the pointer
    int argc = *(&start_ptr - 1);

    /* Initialise the heap for this process */
    init_heap();

    /* Call exit syscall on the return value of main */
    exit(main(*(&argc - 1), argv));
}