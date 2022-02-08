
#include "syscall.h"
#include "memory.h"

int main(int argc, char *argv[]);

void _start(int argc, char *argv[]) {
    init_heap();
    exit(main(argc, argv));
}