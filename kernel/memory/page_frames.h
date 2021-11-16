
/*
 * =================================================================================
 *                              Page Frame Allocator
 *      References:
 *             1. https://forum.osdev.org/viewtopic.php?f=1&t=41322
 *             2. https://wiki.osdev.org/Page_Frame_Allocation
 *
 *   This is a bitmap based page frame allocator:
 *      This is a more efficient method of storage than a list, stack or table as it would only require n/8 entries for
 *      n frames
 *      http://shell-storm.org/blog/Physical-page-frame-allocation-with-bitmap-algorithms/
 * */

#ifndef KERNEL_MEMORY_PAGE_H
#define KERNEL_MEMORY_PAGE_H

#include <stdint.h>
#include "mem_common.h"
#include "../../drivers/screen.h"
#include "../../stdlib/stdlib.h"

// 4 kb in bytes
#define PAGE_SIZE 4096

#define KERNEL_SIZE 256
#define MAX_PAGE_TABLE_SIZE 1024

#define null_ptr ((void*)0)

// This should be 32512
#define PAGES_TOTAL ((TOTAL_MEMORY - MEM_START) / PAGE_SIZE)
#define BITMAP_SIZE PAGES_TOTAL/8


/* Reference:
 *      1. https://wiki.osdev.org/Page_Frame_Allocation
 *      2. https://stackoverflow.com/questions/29945171/difference-between-page-table-and-page-directory
 *      3. https://stackoverflow.com/questions/13970259/how-does-this-way-of-writing-data-to-a-specific-physical-memory-address-work
 * */

uint8_t frames[BITMAP_SIZE];

uint32_t free_frames;

// The address of the a frame number is given by:
//   addr = inital_offset + (frame_num * PAGE_SIZE)
void *get_frame_addr(uint32_t frame_num) {
    return (void *)(MEM_START + frame_num * PAGE_SIZE);
}

uint32_t get_frame_num(uint32_t addr) {
    return (addr - MEM_START) / PAGE_SIZE;
}

void free_page_frame(uint32_t addr) {
    int frame_num = get_frame_num(addr);
    // Set to used
    frames[frame_num/8] &= ~(1 << (frame_num % 8));
    free_frames++;
}

// TODO: need to add a more readable implementation
unsigned int alloc_page_frame() {
    unsigned char mapEntry;
    for(int i = 0; i < BITMAP_SIZE ; i++) {
        mapEntry = frames[i];
        for(int j = 0; j < 8; j++) {
            if(((mapEntry >> j) & 1) == 0) {
                int frame_num = (i*8)+j;
                // Set as in use
                frames[frame_num/8] |= 1 << (frame_num % 8);
                free_frames--;
                return frame_num;
            }
        }
    }

    return null_ptr;
}

void init_mem() {
    free_frames = PAGES_TOTAL;
    // Set all frames to unused
    for(int i = 0; i < BITMAP_SIZE; i++) {
        frames[i] = 0;
    }
}


#endif //KERNEL_MEMORY_PAGE_H
