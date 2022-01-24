
#include "../stdlib/stdlib.h"

int main(int argc, const char *argv[]) {
    // This should cause an error
    asm volatile ("mov %0, %%eax;"
                  "int $0x80;"
    : : "r" (argc)
    : "eax"
    );

    asm volatile("hlt");

    while(1);
}
