
#include "stdlib.h"
#include "syscall.h"
#include "string.h"
#include "../drivers/screen.h"

// Disable stdlib C redefinitions warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wincompatible-library-redeclaration"

#define BINARY 2
#define OCTAL 8
#define DECIMAL 10
#define HEXADECIMAL 16

static char printf_color = 0x0f;

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
    while(i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

/* THe bellow has been copied from https://www.techiedelight.com/implement-itoa-function-in-c/ for debugging ints*/
// Iterative function to implement `itoa()` function in C
char *itoa(int value, char *buffer, int base) {
    // invalid input
    if(base < 2 || base > 32) {
        return buffer;
    }

    // consider the absolute value of the number
    int n = abs(value);

    int i = 0;
    while(n) {
        int r = n % base;

        if(r >= 10) {
            buffer[i++] = 65 + (r - 10);
        } else {
            buffer[i++] = 48 + r;
        }

        n = n / base;
    }

    // if the number is 0
    if(i == 0) {
        buffer[i++] = '0';
    }

    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if(value < 0 && base == 10) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

void strcpy(const char *src, void *dest) {
    char *d = dest;
    const char *s = src;
    int i;
    for(i = 0; src[i] != '\0'; i++)
        d[i] = s[i];
    d[i] = '\0';
}

char *sprintf_args(char *str, const char *format, va_list args) {
    char temp[40];
    int i = 0;
    int buf_count = 0;
    char *temp_str;
    while(format[i]) {
        if(format[i] == '%') {
            i++;
            switch (format[i]) {
                case 'd':
                    itoa(va_arg(args,long), temp, DECIMAL);
                    strcpy(temp, &str[buf_count]);
                    buf_count += strlen(temp);
                    break;
                case 's':
                    temp_str = va_arg(args,char*);
                    strcpy(temp_str, &str[buf_count]);
                    buf_count += strlen(temp_str);
                    break;
                case 'o':
                    itoa(va_arg(args,long), temp, OCTAL);
                    strcpy(temp, &str[buf_count]);
                    buf_count += strlen(temp);
                    break;
                case '%':
                    str[buf_count++] = '%';
                    break;
                case 'c':
                    str[buf_count++] = va_arg(args,long);
                    break;
                case 'p':
                    itoa(va_arg(args,int), temp, HEXADECIMAL);
                    strcpy(temp, &str[buf_count]);
                    buf_count += strlen(temp);
                    break;
                case 'b':
                    itoa(va_arg(args,long), temp, BINARY);
                    strcpy(temp, &str[buf_count]);
                    buf_count += strlen(temp);
                    break;
                default:

            }
        } else {
            str[buf_count++] = format[i];
        }
        i++;
    }

    // End string
    str[buf_count] = '\0';
    return str;
}

char *sprintf(char *str, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char *result = sprintf_args(str, format, args);
    va_end(args);
    return result;
}

void printf_c(char colour, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    sprintf_args(buffer, format, args);
    va_end(args);
    print_syscall(buffer, colour);
}

void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    sprintf_args(buffer, format, args);
    va_end(args);
    print_syscall(buffer, 0x0f);
}

void println(void) {
    print_syscall("\n", 0x0f);
}

#pragma clang diagnostic pop
