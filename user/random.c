

int main(int argc, const char *argv[]) {

    char *tex = "this is the text we want";
//    int b = 4;
//
//    // This should cause an error
//    asm volatile ("mov %0, %%eax;"
//                  "int $0x80;"
//    : : "r" (&b)
//    : "eax"
//    );
////
    asm("mov %0, %%edi;"
        "mov %1, %%esi;"
        "mov %2, %%eax;"
        "int $0x80;"
    : : "r" (&tex), "r" (0x0f), "r" (2)
    : "eax", "edi", "esi"
    );


    asm volatile ("mov %0, %%eax;"
                  "int $0x80;"
    : : "r" (0)
    : "eax"
    );
}
