
#include "kstdlib.h"
#include <stdarg.h>
#include "../drivers/screen.h"
#include "../stdlib/stdlib.h"

void kprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char str[1024];
    char *result = sprintf_args(str, format, args);
    va_end(args);
    print_string(result);
}

void kprintf_c(char colour, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char str[1024];
    char *result = sprintf_args(str, format, args);
    va_end(args);
    print_string_colour(result, colour);
}