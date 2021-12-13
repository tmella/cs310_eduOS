
#include "heap.h"
#include "mem_common.h"
#include "../../drivers/screen.h"
#include "../../stdlib/stdlib.h"

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

static heap_segment_t *heap_start;

void set_heap_elem(heap_segment_t *elem, uint32_t size,
                   uint8_t alloc, heap_segment_t *next, heap_segment_t *prev) {
    elem->size = size;
    elem->is_allocated = alloc;
    elem->next = next;
    elem->previous = prev;
}

void init_heap() {
    heap_start = (heap_segment_t *) KERNEL_HEAP_START; // Made up address needs fixing
    set_heap_elem(heap_start, KERNEL_HEAP_SIZE - sizeof(heap_segment_t),
                  0, null_ptr, null_ptr);
}

void *k_malloc(uint32_t no_bytes) {
    heap_segment_t *chosen_segment = null_ptr;
    heap_segment_t *optimal_search = heap_start;

    uint32_t best_alloc = 0x7FFFFFFF;

    // Iterates over all segments to find the best fits
    while (optimal_search != null_ptr) {
        if (!optimal_search->is_allocated) {
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
    if (chosen_segment == null_ptr)
        return null_ptr;

    // TODO: what if the other segment isnt worth it?
    heap_segment_t *next_elem = chosen_segment->next;

    // FIXME: this causes a fragmentation issue
    // Solution allocate the rest of the meory as padding
    if (chosen_segment->size - no_bytes - sizeof(heap_segment_t) > sizeof(heap_segment_t)) {
        next_elem = (heap_segment_t *) (((void *) chosen_segment) + no_bytes + sizeof(heap_segment_t));
        next_elem->previous = chosen_segment;
        next_elem->next = null_ptr;
        next_elem->size = chosen_segment->size - no_bytes - sizeof(heap_segment_t);
        next_elem->is_allocated = 0;
    }

    // Only take the amount we need
    chosen_segment->size = no_bytes; // TODO: do I need to subtract sizeOf(SEGMENT)
    chosen_segment->is_allocated = 1;
    chosen_segment->next = next_elem;

    return (void *) chosen_segment + sizeof(heap_segment_t);
}

void merge_free_memory(heap_segment_t *current) {
    // Consume the right if its free
    while (current->next != null_ptr && !(current->next->is_allocated)) {
        current->size += current->next->size + sizeof(heap_segment_t);
        current->next = current->next->next;
    }
    // Left
    while (current->previous != null_ptr && !current->previous->is_allocated) {
        current->size += current->previous->size + sizeof(heap_segment_t);
        current->previous = current->previous->previous;
    }
}

void k_free(void *ptr) {
    if(ptr == null_ptr)
        return;

    heap_segment_t * freeing = ptr - sizeof(heap_segment_t);
    freeing->is_allocated = 0;
    merge_free_memory(freeing);
}


void print_seg(heap_segment_t *seg) {
    char val[10];
    print_string("Allocated with size ");
    print_string(itoa(seg->size, val, 10));

    if(seg->is_allocated) {
        print_string(" it is allocated ");
    } else {
        print_string(" it is not allocated ");
    }
    print_string("at address ");
    print_string(itoa((void *) seg + sizeof(heap_segment_t), val, 16));
}

void debug() {
    heap_segment_t *elem = heap_start;
    while (elem != null_ptr) {
        print_new_line();
        print_seg(elem);
        elem = elem->next;
    }
}

void debugt() {
    heap_segment_t *elem = heap_start;
    char val[10];
    while (elem != null_ptr) {
        print_string("\nDoing this ");
        print_string("at address ");
        print_string(itoa(elem, val, 16));
//        print_new_line();
//        print_seg(elem);
        elem = elem->next;
//        elem = null_ptr;
    }

}