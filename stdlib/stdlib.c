
#include <stdarg.h>
#include "../drivers/screen.h"

// Disable stdlib C redefinitions
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"

#define OCTAL 8
#define DECIMAL 10
#define HEXADECIMAL 16

int abs(int value) {
    return value * ((value > 0) - (value < 0));

}

// Function to swap two numbers
void swap(char *x, char *y) {
    char t = *x;
    *x = *y;
    *y = t;
}

// Function to reverse `buffer[i…j]`
char *reverse(char *buffer, int i, int j) {
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

/* THe bellow has been copied from https://www.techiedelight.com/implement-itoa-function-in-c/ for debugging ints*/
// Iterative function to implement `itoa()` function in C
char *itoa(int value, char *buffer, int base) {
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }

    // consider the absolute value of the number
    int n = abs(value);

    int i = 0;
    while (n) {
        int r = n % base;

        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        } else {
            buffer[i++] = 48 + r;
        }

        n = n / base;
    }

    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }

    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

unsigned int sleep(unsigned int ms) {

}

void strcpy(const char *src, void *dest) {
    char *d = dest;
    const char *s = src;
    int i;
    for (i = 0; src[i]; i++)
        d[i] = s[i];
    d[i] = 0;
}

void *memset(void *src, void *dest, int n) {
    char *d = dest;
    const char *s = src;
    for (int i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}

void printf(const char *format, ...) {
    // Size is max INT
    char var_temp[12];
    char string_buff[100];
    va_list args;
    va_start(args, format);

    for (int i = 0; format[i]; i++) {
        if (format[i] == '%') {
            i++;
            switch (format[i]) {
                case 'd':
                    itoa(va_arg(args,
                    int), var_temp, DECIMAL);
                    print_string(var_temp);
                    break;
                case 's':
                    print_string(va_arg(args,
                    char*));
                    break;
                case 'o':
                    break;
                case 'x':
                    break;
                case '%':
                    break;
            }
        } else {
            print_char(format[i]);
        }
    }

    va_end(args);
}
#pragma clang diagnostic pop