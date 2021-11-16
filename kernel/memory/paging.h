
#ifndef CSWK_KERNEL_MEMORY_PAGING_H
#define CSWK_KERNEL_MEMORY_PAGING_H


/* Reference:
 *      1. https://stackoverflow.com/questions/29945171/difference-between-page-table-and-page-directory
 *      2. https://wiki.osdev.org/Page_Frame_Allocation
 *
 * */
typedef struct {
  uint8_t allocated;
  uint8_t kernel_mode;
  uint8_t reserved;
  uint32_t frame_address;
}__attribute__((packed)) page_entry_t;

#endif //CSWK_KERNEL_MEMORY_PAGING_H
