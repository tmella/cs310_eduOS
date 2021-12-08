
#ifndef CSWK_KERNEL_MEMORY_MEM_COMMON_H
#define CSWK_KERNEL_MEMORY_MEM_COMMON_H

// Set in the bootloader and set by Linker
#define KERNEL_START 0x10000

// QEMU by default sets memory to 128
#define TOTAL_MEMORY 1024 * 1024 * 128

// TODO: check if too much memory
#define KERNEL_HEAP_START 0x200000
#define KERNEL_HEAP_SIZE 0x100000

#define FRAMES_START 0x300000
#define FRAME_SIZE 4096 // In bytes
#define FRAME_SIZE_HEX 0x1000

#define FRAMES_NO (MEMORY_END-FRAMES_START)/FRAME_SIZE_HEX



// TODO need to decide the heap start address and size
// TODO need to figure out what happens with the STACK and size

#define MEMORY_END 0x8000000

#endif //CSWK_KERNEL_MEMORY_MEM_COMMON_H
