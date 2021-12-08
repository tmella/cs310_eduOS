//
// Created by University  on 26/11/21.
//

#ifndef CSWK_STDLIB_STDLIB_H
#define CSWK_STDLIB_STDLIB_H

/* THe bellow has been coppied from https://www.techiedelight.com/implement-itoa-function-in-c/ for debugging ints*/

void sleep(unsigned int ms);

int abs(int value);

// Function to swap two numbers
void swap(char *x, char *y);

// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j);

// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base);

// TODO: should this be here
void *memset(void *s, int c, int n);

#endif //CSWK_STDLIB_STDLIB_H
