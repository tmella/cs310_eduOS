
#include "include/task1.h"

#include "../../../stdlib/stdlib.h"
#include "../../../stdlib/syscall.h"

#define RED_ON_BLACK 0x04

void welcome_process() {
    // TODO: create a basic method perhaps with a welcome method
    printf_c(RED_ON_BLACK, "\nWelcome to the Educational Operating System\n");
    exit(0);
}


