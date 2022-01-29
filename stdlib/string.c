
/*  String.h
 *
 *  This file includes std helper functions on strings
 * */

#include "string.h"

int strlen(const char *str) {
    int i = 0;
    while(str[i])
        i++;
    return i;
}

int strcmp(const char *str1, const char *str2) {
    while(*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char *) str1 - *(const unsigned char *) str2;
}