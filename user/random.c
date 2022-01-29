

int main(int argc, const char *argv[]) {

//    char **val = (char **) 0x400000;
//    *val = "a";
//
    char *t = "SOME OTHER TEXT";
//    char text[16] = "For fuck sake";

//    asm("mov %0, %%edi;"
//        "mov %1, %%esi;"
//        "mov %2, %%eax;"
//        "int $0x80;"
//    : : "r" (&text), "r" (0x0f), "r" (2)
//    : "eax", "edi", "esi"
//    );

    asm("mov %0, %%edi;"
        "mov %1, %%esi;"
        "mov %2, %%eax;"
        "int $0x80;"
    : : "r" (&t), "r" (0x0f), "r" (2)
    : "eax", "edi", "esi"
    );


    asm volatile ("mov %0, %%eax;"
                  "int $0x80;"
    : : "r" (0)
    : "eax"
    );

}
