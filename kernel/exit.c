
/* ================== Exit system call ================== */

/*
 * Guide on how to write assembly in c:
 *      https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Extended-Asm
 * */

void k_exit() {
    asm("mov %0, %%eax \n\t"
        "int $0x80"
    : : "r" (1)
    );
}

