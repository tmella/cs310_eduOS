
#include "syscall.h"

int main(int argc, const char *argv[]) {

    char *t = "SOME OTHER TEXT";

    asm("mov %0, %%edi;"
        "mov %1, %%esi;"
        "mov %2, %%eax;"
        "int $0x80;"
    : : "r" (t), "r" (0x0f), "r" (2)
    : "eax", "edi", "esi"
    );


    exit(0);
}
