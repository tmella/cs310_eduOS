
#include <stdint.h>
#include "mem_common.h"
#include "frame_allocator.h"


// Bitmap to keep track of frames
uint8_t frames[BITMAP_SIZE];

// Counter for number of free frames
uint32_t free_frames;


// The address of the a frame number is given by:
//   addr = inital_offset + (frame_num * PAGE_SIZE)
void *get_frame_addr(uint32_t frame_num) {
    return (void *)(FRAMES_START + frame_num * FRAME_SIZE);
}

uint32_t get_frame_num(uint32_t addr) {
    return (addr - FRAMES_START) / FRAME_SIZE;
}

void free_page_frame(uint32_t addr) {
    int frame_num = get_frame_num(addr);
    // Set to used
    frames[frame_num/8] &= ~(1 << (frame_num % 8));
    free_frames++;
}

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

    print_string("There are no more free pages");
    return -1;
}

void *alloc_frame_addr() {
    return get_frame_addr(alloc_page_frame());
}

void init_mem() {
    free_frames = FRAMES_NO;
    // Set all frames to unused
    for(int i = 0; i < BITMAP_SIZE; i++) {
        frames[i] = 0;
    }
}
