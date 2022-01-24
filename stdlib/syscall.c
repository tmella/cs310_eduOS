
#include "exit.h"
#include "../kernel/syscalls.h"

void exit(int code) {
    asm volatile ("mov %0, %%eax;"
                  "int $0x80;"
    : : "r" (SYSCALL_PROCESS_EXIT)
    : "eax"
    );
}

void sleep(unsigned int ms) {
    asm("mov %0, %%edi;"
        "mov %1, %%eax;"
        "int $0x80;"
    : : "r" (ms), "r" (SYSCALL_PROCESS_SLEEP)
    : "eax", "edi"
    );
}

void print_syscall(unsigned int colour, char *text) {
    asm("mov %0, %%edi;"
        "mov %1, %%ebx;"
        "mov %2, %%eax;"
        "int $0x80;"
    : :
    "r" (colour),
    "r" (text),
    "r" (SYSCALL_PRINT_SCREEN)
    : "eax", "edi", "ebx"
    );
}
