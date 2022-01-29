
#include "syscall.h"
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

void print_syscall(char *text, unsigned int colour) {
    asm("mov %0, %%edi;"
        "mov %1, %%esi;"
        "mov %2, %%eax;"
        "int $0x80;"
    : : "r" (text), "r" (colour), "r" (SYSCALL_PRINT)
    : "eax", "edi", "esi"
    );
}

