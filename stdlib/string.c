
/*  String.h
 *
 *  This file includes std helper functions on strings
 * */

#include "string.h"

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

int next_word(const char *str1, char *str2) {
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