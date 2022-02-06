
#ifndef CSWK_KERNEL_MEMORY_HEAP_H
#define CSWK_KERNEL_MEMORY_HEAP_H

#include <stdint.h>


void init_kheap();

void k_free(void *addr);
void *k_malloc(uint32_t bytes);


#endif //CSWK_KERNEL_MEMORY_HEAP_H
