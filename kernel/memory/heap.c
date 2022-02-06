
#include "heap.h"
#include "mem_common.h"
#include "../../drivers/screen.h"
#include "../kstdlib.h"

#define null_ptr ((void*)0)

/*
 * The HEAP essentially a linked list that ranges from 0x100000 to 0x2000000
 *
 *  Perhaps this size is slightly too large for a regular OS however given that this
 *  OS won't be dealing with a large volume of User programs so an overly large Heap
 *  should not be an issue
 *
 * */

typedef struct heap_segment {
  struct heap_segment *next;
  struct heap_segment *previous;

  uint32_t size;
  uint8_t is_allocated;
} heap_segment_t;

#define data_start(s) ((void *) s + sizeof(heap_segment_t))

static heap_segment_t *heap_start;

void print_seg(heap_segment_t *seg);

void set_kheap_elem(heap_segment_t *elem, uint32_t size,
                   uint8_t alloc, heap_segment_t *next, heap_segment_t *prev) {
    elem->size = size;
    elem->is_allocated = alloc;
    elem->next = next;
    elem->previous = prev;
}

void init_kheap() {
    heap_start = (heap_segment_t *) KERNEL_HEAP_START; // Made up address needs fixing
    set_kheap_elem(heap_start, KERNEL_HEAP_SIZE - sizeof(heap_segment_t),
                  0, null_ptr, null_ptr);
}

uint8_t validate_seg(heap_segment_t * segment) {
    if(segment->next == null_ptr) {
        return 1;
    }
    return (((void *)segment) + sizeof(heap_segment_t) + segment->size) - ((void *) segment->next) <= 0;
}

void *k_malloc(uint32_t no_bytes) {
    heap_segment_t *chosen_segment = null_ptr;
    heap_segment_t *optimal_search = heap_start;

    uint32_t best_alloc = 0x7FFFFFFF;

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
        kprintf("PANIC kmalloc failed to allocate memory");
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

    // Validation
    if(!validate_seg(chosen_segment)) {
        kprintf("PANIC, Kmalloc failed the sanity check");
        while(1);
    }

    return data_start(chosen_segment);
}

void merge_free_memory(heap_segment_t *current) {
    heap_segment_t *left_most = current;
    while(left_most->previous != null_ptr && !left_most->previous->is_allocated){
        left_most = left_most->previous;
    }

    // Consume the right if its free
    while (left_most->next != null_ptr && !(left_most->next->is_allocated)) {
        left_most->size += left_most->next->size + sizeof(heap_segment_t);
        left_most->next = left_most->next->next;
    }
}

void k_free(void *ptr) {
    if(ptr == null_ptr)
        return;

    heap_segment_t * freeing = ptr - sizeof(heap_segment_t);
    freeing->is_allocated = 0;
    merge_free_memory(freeing);
}
