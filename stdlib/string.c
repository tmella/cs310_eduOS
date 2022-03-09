
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

int first_word(const char *str1, char *str2) {
    char whitespace = 1;
    int str2counter = 0;
    for(int i = 0; i < strlen(str1); i++) {
        if(str1[i] == ' ') {
            if(!whitespace)
                break;
        } else {
            whitespace = 0;
            str2[str2counter++] = str1[i];
        }
    }
    str2[str2counter] = '\0';
    return str2counter;
}