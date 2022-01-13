
#include "memory.h"

void *memset(void *dest, int val, int n) {
    unsigned char *ptr = dest;
    while(n--)
        *ptr++ = val;
    return dest;
}


void *memcpy(void *src, void *dest, int n) {
    char *d = dest;
    const char *s = src;
    for (int i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}