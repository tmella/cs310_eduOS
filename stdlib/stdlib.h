
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

// TODO: should this be here (check if I should add it to a memory based file)
void *memset(void *src, const void *dest, int n);

void printf(const char *format, ...);

#endif //CSWK_STDLIB_STDLIB_H
