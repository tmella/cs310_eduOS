
// TODO need to add a standard header to all files with a detailed explanation of funcitonality
// Also need to explain some impl details/choices taken

#ifndef CSWK_KERNEL_MEMORY_PAGING_H
#define CSWK_KERNEL_MEMORY_PAGING_H

#include "stdint.h"

/*
 * Properties described in the following page:
 *
 * Interesting link on paging decisions (random forum): https://groups.google.com/g/alt.os.development/c/QAcC9_Nch5c
 *
 *
 * */

// Using a bit field for the struct instead of bytes as it will be easier to read/understand
// The size of this struct is 32 bits
typedef struct {
  unsigned int present: 1; // Set if page is present in physical mem
  unsigned int wr: 1; // If set can be written to
  unsigned int us: 1; // If set can be accessed by user
  unsigned int pwt: 1; // If enabled then write through caching is enabled
  unsigned int pcd: 1; // If set then page not cached
  unsigned int accessed: 1; // Set if it was has been read during an address translation
  unsigned int dirty: 1; // Set if page has been written to
  unsigned int page_size: 1; // Must be set to 0, if set then maps to page 4MB
  unsigned int available: 4; //
  unsigned int physical_addr: 20;
} page_t;

typedef struct {
  page_t entry[1024];
} page_directory_t;

typedef struct {
  page_t entry[1024];
} page_table_t;

void print_if_set(unsigned int flag);

// Used to debug
void print_page(page_t *page);

/* Given that the address stored in the table is only 20 bits the address needs shifting by 12 bits
 * as a page address is 12 bits smaller that the address bus size
 * Detailed explanation can be found here: https://stackoverflow.com/questions/26858196/why-does-page-directory-entries-need-20-bits-to-point-210-page-tables
 */
unsigned int table_addr(void *p_address);

unsigned int table_to_pAddr(void *table_addr);

void set_page(page_t *page, void *p_address, unsigned int p, unsigned int wr, unsigned int us);

void map_page(page_directory_t *dir, uint32_t *v_address, uint32_t *p_address, uint32_t p, uint32_t wr, uint32_t us);

void enable_paging();

// TODO: still needs testing
void *get_p_address(uint64_t *v_address);

void set_page_dir(page_directory_t *dir);

void init_paging();

void create_kmapped_table();

#endif //CSWK_KERNEL_MEMORY_PAGING_H
