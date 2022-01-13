
#include "paging.h"
#include "../../stdlib/stdlib.h"
#include "../../drivers/screen.h"
#include "frame_allocator.h"

page_directory_t *page_directory;

void print_if_set(unsigned int flag) {
    if (flag)
        print_string("1");
    else
        print_string("0");
}


// Used to debug
void print_page(page_t *page) {
    print_new_line();
    print_if_set(page->present);
    print_if_set(page->wr);
    print_if_set(page->us);
    print_if_set(page->pwt);
    print_if_set(page->pcd);
    print_if_set(page->accessed);
    print_if_set(page->dirty);
    print_if_set(page->page_size);

    print_new_line();
    char buf[15];
    print_string(itoa(page->available, buf, 2));

    print_new_line();
    char buffer[50];
    print_string(itoa(page->physical_addr, buffer, 16));
    print_new_line();
}

/* Given that the address stored in the table is only 20 bits the address needs shifting by 12 bits
 * as a page address is 12 bits smaller that the address bus size
 * Detailed explanation can be found here: https://stackoverflow.com/questions/26858196/why-does-page-directory-entries-need-20-bits-to-point-210-page-tables
 */
unsigned int table_addr(void *p_address) {
    return ((unsigned int) p_address) >> 12;
}

unsigned int table_to_pAddr(void *table_addr) {
    return ((unsigned int) table_addr) << 12;
}

void set_page(page_t *page, void *p_address, unsigned int p, unsigned int wr, unsigned int us) {
    page->present = p;
    page->wr = wr;
    page->us = us;
    page->pwt = 0;
    page->pcd = 0;
    page->accessed = 0;
    page->dirty = 0;
    page->page_size = 0; // Must always be 0
    page->available = 0;
    page->physical_addr = table_addr(p_address);
}

void map_page(page_directory_t *dir, uint32_t *v_address, uint32_t *p_address, uint32_t p, uint32_t wr, uint32_t us) {
    unsigned long page_dir_index = (unsigned long) v_address >> 22;
    unsigned long page_tab_index = (unsigned long) v_address >> 12 & 0x03FF;

    page_t *page_tab_ent = &dir->entry[page_dir_index];

    page_table_t *page_table;

    if (!page_tab_ent->present) {
        page_table = (page_table_t *) alloc_frame_addr();
        // This could potentially an issue us = 1
        set_page(page_tab_ent, page_table, 1, 1, 1);
    } else {
        page_table = (page_table_t *) table_to_pAddr(page_tab_ent->physical_addr);
    }

    page_t *page = &page_table->entry[page_tab_index];

    set_page(page, p_address, p, wr, us);
}

void enable_paging() {
    asm volatile("movl %cr0, %eax");
    asm volatile("orl $0x80000001, %eax");
    asm volatile("movl %eax, %cr0");
}



// TODO: still needs testing
void *get_p_address(uint64_t *v_address) {
//    unsigned long page_dir_index = (unsigned long) v_address >> 22;
//    unsigned long page_tab_index = (unsigned long) v_address >> 12 & 0x03FF;
//
//    page_t *page_table_entry = &(page_directory->entry[page_dir_index]);
//    if(!page_table->present)
//        return 0; // Maybe null?
//
//    page_table_t *table = &(page_table_entry->physical_addr << 12);
//    page_t *ent = *(table->entry[page_tab_index]);
//
//    if(!ent->present)
//        return 0;
//
//    return ent->physical_addr << 12;
}

void set_page_dir(page_directory_t *dir) {
    asm volatile ("mov %0, %%eax;"
                  "mov %%eax, %%cr3"
    : : "r" (dir)
    : "eax"
    );
}

void init_paging() {
    // Set the page directory at 0x100000 where main mem starts and will be 4096 aligned
    page_directory = alloc_frame_addr();

    // Blanking page directory, by setting all entries to
    // not present, read-write, kernel (all else zeroed by default)
    for (int i = 0; i < 1024; i++)
        set_page(&page_directory->entry[i], 0, 0, 0, 0);

    // IDENTITY MAP EVERYTHING (as a starting point)
    for (int i = 0; i < 0x400000; i += FRAME_SIZE){
        map_page(page_directory, i, i, 1, 1, 0);
    }

    set_page_dir(page_directory);

    enable_paging();
}

/* At the moment there is no user space therefore there is no distinction
 * between user and kernel stack */
page_directory_t *create_kmapped_table() {
    page_directory_t *directory = (page_directory_t *) alloc_frame_addr();
    for (int i = 0; i < 1024; i++)
        set_page(&directory->entry[i], 0, 0, 0, 0);

    // Identity map everything from kernel to FRAMES MEMORY
    // Ideally we could get the size of the kernel from a linker
    // and we can map more accurately
    // This includes kernel code/heap
//    for (int i = 0; i < FRAMES_START + 4; i += FRAME_SIZE)
//        map_page(directory, i, i, 1, 1, 0);

//     TODO check if the permissions are correct
//    map_page(directory, directory, directory, 1, 1, 0 );
//    for(int i= 1; i<=3; i++)
//        map_page(directory, (directory) + (i * FRAME_SIZE), (directory) + (i * FRAME_SIZE), 1, 1, 0);

}


void page_fault_handler(i_registers_t *regs) {
    asm volatile("sti");
    printf("A page fault has occurred with the following address %p", regs->eax);
    while(1);
}

