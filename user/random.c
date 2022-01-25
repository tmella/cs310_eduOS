

int main(int argc, const char *argv[]) {

    int a = 4;
    int b = 4;

    // This should cause an error
    asm volatile ("mov %0, %%eax;"
                  "int $0x80;"
    : : "r" (a)
    : "eax"
    );

    asm volatile ("mov %0, %%eax;"
                  "int $0x80;"
    : : "r" (b)
    : "eax"
    );


    asm volatile ("mov %0, %%eax;"
                  "int $0x80;"
    : : "r" (0)
    : "eax"
    );
}
