
#ifndef CSWK_STDLIB_MEM_H
#define CSWK_STDLIB_MEM_H

void *memset(void *dest, int val, int n);
void *memcpy(void *src, void *dest, int n);

void init_heap();
void *malloc(int bytes);

#endif //CSWK_STDLIB_MEM_H
