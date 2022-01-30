

int main(int argc, char *argv[]);

void _start(int argc, char *argv[]) {
    int result = main(argc, argv);

    // TODO need to link stdlib
    asm volatile ("mov %0, %%eax;"
                  "mov %1, %%edi;"
                  "int $0x80;"
    : : "r" (0), "r" (result)
    : "eax", "edi"
    );
}