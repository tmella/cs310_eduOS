
#ifndef CSWK_KERNEL_MEMORY_COMMON_H
#define CSWK_KERNEL_MEMORY_COMMON_H

// QEMU by default sets memory to 128
#define TOTAL_MEMORY 1024 * 1024 * 128

// We will start paging from here
// Everything above this should not be allowed
// Image to example: https://images.app.goo.gl/bm5n5CAdcAnVEJb96
#define MEM_START 0x100000


#endif //CSWK_KERNEL_MEMORY_COMMON_H
