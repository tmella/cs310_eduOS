
#include "memory.h"
#include "stdlib.h"

#define null_ptr ((void*)0)

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

typedef struct heap_segment {
  struct heap_segment *next;
  struct heap_segment *previous;

  unsigned int size;
  unsigned char is_allocated;
} heap_segment_t;

heap_segment_t *heap_start;

void set_heap_elem(heap_segment_t *elem, unsigned int size,
                   unsigned char alloc, heap_segment_t *next, heap_segment_t *prev) {
    elem->size = size;
    elem->is_allocated = alloc;
    elem->next = next;
    elem->previous = prev;
}

void init_heap() {
    heap_start = (heap_segment_t *) 0x600000;// (heap_segment_t *) 0x600000;
    set_heap_elem(heap_start, 0x1000 - sizeof(heap_segment_t), 0, null_ptr, null_ptr);
}


void *malloc(int no_bytes) {
    heap_segment_t *chosen_segment = null_ptr;
    heap_segment_t *optimal_search = heap_start;

    unsigned int best_alloc = 0x7FFFFFFF;

    // Iterates over all segments to find the best fits
    while (optimal_search != null_ptr) {
        if (!optimal_search->is_allocated) {
            // I think this is wasteful check
            if (optimal_search->size >= no_bytes + sizeof(heap_segment_t)) {
                if (optimal_search->size <= best_alloc) {
                    best_alloc = optimal_search->size;
                    chosen_segment = optimal_search;
                }
            }
        }
        optimal_search = optimal_search->next;
    }

    // No memory. Should I add a debug error message. Is that possible in a Kernel
    if (chosen_segment == null_ptr) {
        printf("PANIC kmalloc failed to allocate memory");
        while(1);
    }

    if (chosen_segment->size - (no_bytes + sizeof(heap_segment_t)) > 0) {
        // If its worth partitioning
        heap_segment_t *cur_next = chosen_segment->next;
        heap_segment_t *empty_next = (heap_segment_t *) (((void *) chosen_segment + sizeof(heap_segment_t)) + no_bytes);
        empty_next->size = chosen_segment->size - no_bytes - sizeof(heap_segment_t);
        empty_next->previous = chosen_segment;
        empty_next->next = cur_next;
        empty_next->is_allocated = 0;

        chosen_segment->size = no_bytes;
        chosen_segment->next = empty_next;
        // previous wil be the same
        chosen_segment->is_allocated = 1;
    } else {
        // Its not worth fragmenting size approx. no_bytes needed
        chosen_segment->is_allocated = 1;
        // We leave the size as is
        // next and prev remain the same
    }

    return (void *) chosen_segment + sizeof(heap_segment_t);
}