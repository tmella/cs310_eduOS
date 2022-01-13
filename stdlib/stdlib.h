
#ifndef CSWK_STDLIB_STDLIB_H
#define CSWK_STDLIB_STDLIB_H

/* THe bellow has been coppied from https://www.techiedelight.com/implement-itoa-function-in-c/ for debugging ints*/

int abs(int value);

// Function to swap two numbers
void swap(char *x, char *y);

// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j);

// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base);

void println(void);
void printf(const char *format, ...);
void printf_c(char colour, const char *format, ...);
void set_print_color(char color);

#endif //CSWK_STDLIB_STDLIB_H
