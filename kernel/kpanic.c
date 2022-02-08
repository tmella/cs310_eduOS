
#include "kpanic.h"
#include "stdlib.h"
#include "../drivers/screen.h"
_Noreturn void PANIC(const char *format, ...) {
    print_string_colour("PANIC: ", 0x04);
    char buffer[1024];
    va_list args;
    va_start(args, format);
    print_string(sprintf_args(buffer, format, args));
    va_end(args);
    while(1);
}

