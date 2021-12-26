
#include "exit.h"


void exit(int code) {
    asm volatile ("mov %0, %%eax;"
        "int $0x80;"
    : : "r" (code)
    : "eax"
    );
}



