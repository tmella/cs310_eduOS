
/*
 * The GDT is currently created in the bootloader
 * this class allows us to manipulate it afterwards.
 *
 * This is intended mainly for small modifications as
 * all the other logic is located in bootloader/gdt.asm
 *
 * TSS reference: https://wiki.osdev.org/Getting_to_Ring_3
 * */

#include "gdt.h"
#include "tss.h"

#include "../x86/x86_32.h"

#include "../../stdlib/memory.h"

struct gdt_ptr {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

struct gdt_entry {
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_high;
} __attribute__((packed));

struct gdt_entry *gdt;

tss_entry_t tss_entry;

/* We want to be able to configure the TSS from C, as
 * it is required for software context switching and
 * that way it is easier for students to comprehend */
void tss_init() {
    struct gdt_entry *tss_gdt = &gdt[5];

    uint32_t base = (uint32_t) & tss_entry;
    tss_gdt->base_low = base & 0xffff;
    tss_gdt->base_middle = (base >> 16) & 0xff;
    tss_gdt->base_high = (base >> 24) & 0xff;

    // Access and granularity are set in bootloader/gdt.asm

    // Zero the TSS
    memset(&tss_entry, 0, sizeof(tss_entry));
    tss_entry.ss0 = 0x10;
    tss_entry.esp0 = get_kstack(); // Extract the current value

    flush_tss();
}

void load_gdt() {
    struct gdt_ptr gp;
    asm volatile ("sgdt %0":"=m"(gp)::"memory");
    gdt = ((struct gdt_entry *) gp.base);
    tss_init();
}

