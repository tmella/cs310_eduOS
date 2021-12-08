
#ifndef CSWK_KERNEL_MEMORY_FRAME_ALLOCATOR_H
#define CSWK_KERNEL_MEMORY_FRAME_ALLOCATOR_H

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

/* References:
 *      1. https://wiki.osdev.org/Page_Frame_Allocation
 *      2. https://stackoverflow.com/questions/29945171/difference-between-page-table-and-page-directory
 *      3. https://stackoverflow.com/questions/13970259/how-does-this-way-of-writing-data-to-a-specific-physical-memory-address-work
 * */

#include <stdint.h>
#include "mem_common.h"
#include "../../drivers/screen.h"

#define BITMAP_SIZE FRAMES_NO/8

void init_mem();

// The address of the a frame number is given by:
//   addr = inital_offset + (frame_num * PAGE_SIZE)
void *get_frame_addr(uint32_t frame_num);

unsigned int alloc_page_frame();
void *alloc_frame_addr();
void free_page_frame(uint32_t addr);

uint32_t get_frame_num(uint32_t addr);


#endif //CSWK_KERNEL_MEMORY_FRAME_ALLOCATOR_H
