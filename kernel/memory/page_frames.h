
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

// The address of the a frame number is given by:
//   addr = inital_offset + (frame_num * PAGE_SIZE)
void *get_frame_addr(uint32_t frame_num);

uint32_t get_frame_num(uint32_t addr);

void free_page_frame(uint32_t addr);

// TODO: need to add a more readable implementation
unsigned int alloc_page_frame();

void *alloc_frame_addr();

void init_mem();


#endif //KERNEL_MEMORY_PAGE_H
