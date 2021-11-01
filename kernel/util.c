

#include "util.h"

/*
 * Method which copies a certain number of bytes (bytes)
 * from src to dest
 */
void memory_copy(const char* src, char* dest, int bytes) {
    for(int i = 0; i < bytes ; i++)
        *(dest + i) = *(src + i);
}
