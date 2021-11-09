
#ifndef MEMORY_HEAP_H
#define MEMORY_HEAP_H

#define HEAP_START_ADDRESS 0x0998888 // FIXME you made it up
#define HEAP_SIZE 1024 * 4 // 4KB
#define HEAP_SEGMENT_SIZE sizeof(heap_segment_t)

#include <stdint.h>

typedef struct heap_segment {
  struct heap_segment *next;
  struct heap_segment *previous;

  uint32_t size;
  uint8_t is_allocated;
} heap_segment_t;


void init_heap();

void *kmalloc(uint32_t no_bytes);
void kfree(void *ptr);


#endif //MEMORY_HEAP_H
