
#ifndef MEMORY_HEAP_H
#define MEMORY_HEAP_H

#define HEAP_START_ADDRESS 0x0998888 // FIXME you made it up

#include <stdint.h>

static heap_segment_t *head_start;

typedef struct segment {
  heap_segment_t *next;
  heap_segment_t *previous;

  uint32_t size;
  uint8_t is_allocated;
} heap_segment_t;

void *kmalloc(uint32_t no_bytes);


void init_heap() {
    head_start = HEAP_START_ADDRESS;
};

#endif //MEMORY_HEAP_H
