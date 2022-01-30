
int main(int argc, const char *argv[]) {

    char *t = "Random just prints this value";

    asm("mov %0, %%edi;"
        "mov %1, %%esi;"
        "mov %2, %%eax;"
        "int $0x80;"
    : : "r" (t), "r" (0x0f), "r" (2)
    : "eax", "edi", "esi"
    );

    asm volatile ("mov %0, %%eax;"
                  "int $0x80;"
    : : "r" (0)
    : "eax"
    );
}
