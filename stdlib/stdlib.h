
#ifndef CSWK_STDLIB_STDLIB_H
#define CSWK_STDLIB_STDLIB_H

#include "stdarg.h"

/* THe bellow has been copied from https://www.techiedelight.com/implement-itoa-function-in-c/ for debugging ints*/

int abs(int value);

// Function to swap two numbers
void swap(char *x, char *y);

// Function to reverse `buffer[i…j]`
char *reverse(char *buffer, int i, int j);

// Iterative function to implement `itoa()` function in C
char *itoa(int value, char *buffer, int base);

void println(void);
void printf(const char *format, ...);
void printf_c(char colour, const char *format, ...);
void set_print_color(char color);

char *sprintf(char *str, const char *format, ...);
char *sprintf_args(char *str, const char *format, va_list args);
char *sprintf_argsss(char *str, const char *format, va_list args);

#endif //CSWK_STDLIB_STDLIB_H
