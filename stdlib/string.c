
/*  String.h
 *
 *  This file includes std helper functions on strings
 * */

#include "string.h"
#include "stdtypes.h"
#include "stdlib.h"

char isspace(char ch) {
    return ch == '\t' || ch == ' ';
}

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



char *next_word(char *str1) {
    static char* remainder;

    /* Technically unreachable if string formatted correctly */
    return null_ptr;
}

/* Trims whitespace from front and back*/
int strtrim(const char *str, char *trimmed) {
    int start = 0;
    int end = 0;

    for(int i = 0; i < strlen(str); i++)
        if(!isspace(str[i])) {
            start = i;
            break;
        }

    for(int i = strlen(str) - 1; i > 0; i--)
        if(!isspace(str[i])) {
            end = i;
            break;
        }

    int count = 0;
    for(int i = start; i <= end; i++)
        trimmed[count++] = str[i];

    trimmed[count] = '\0';
    return count;
}

char **strwordsplit(const char *str, char **tgt) {

    int wordcount = 0;
    int charcount = 0;

    char trimmed[strlen(str)];

    for(int i = 0; i < strlen(trimmed); i++) {
        if(isspace(str[i])) {
            wordcount++;
            charcount = 0;
        } else {
            tgt[wordcount][charcount++] = str[i];
        }
    }

    return tgt;
}