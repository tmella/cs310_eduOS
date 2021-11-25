
#include "heap.h"
#include "../../stdlib/stdlib.h"
#include "../../drivers/screen.h"

#define null_ptr ((void*)0)

static heap_segment_t *head_start;

void debug_all_segments();

void *kmalloc(uint32_t no_bytes) {
    heap_segment_t *chosen_segment = null_ptr;
    heap_segment_t *optimal_search = head_start;

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
    if(chosen_segment->size - no_bytes - sizeof(heap_segment_t) > sizeof(heap_segment_t)){
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

void init_heap() {
    head_start = (heap_segment_t *) HEAP_START_ADDRESS; // Made up address needs fixing
    head_start->size =
        HEAP_SIZE - sizeof(heap_segment_t); // - heap segment because if not segment size will be overwritten
    head_start->next = null_ptr;
    head_start->previous = null_ptr;
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

void debug_print_segment(heap_segment_t *segment) {
    char size[10];
    print_string("Segment with size ");
    print_string(itoa(segment->size, size, 10));
    if (segment->is_allocated)
        print_string(" is allocated");
    else
        print_string(" is not allocated");

    print_new_line();
}

void debug_all_segments() {
    heap_segment_t *it;
    for(it = head_start ; it != null_ptr; it = it->next)
        debug_print_segment(it);
}

void kfree(void *ptr) {
    if(ptr == null_ptr)
        return;

    heap_segment_t * freeing = ptr - sizeof(heap_segment_t);
    freeing->is_allocated = 0;
    merge_free_memory(freeing);
}

