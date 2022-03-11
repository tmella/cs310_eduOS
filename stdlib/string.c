
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
    if(!str1)
        str1 = remainder;

    if(!str1)
        return null_ptr;
    int max_it = strlen(str1);
    for(int i = 0; i <= max_it; i++) {
        if(*str1 == ' ')
            str1++;
        else if(*str1 == '\0')
            return null_ptr;
        else
            break;
    }

    char *first_word=str1;
    max_it = strlen(str1);
    for(int j  = 0; j <=max_it; j++) {
        if(*str1 == '\0') {
            remainder = null_ptr;
            return first_word;
        } else if (*str1 == ' ') {
            *str1 = '\0';
            remainder = str1+1;
            return first_word;
        }
        str1++;
    }
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