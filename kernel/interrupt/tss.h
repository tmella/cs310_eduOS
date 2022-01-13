
#ifndef CSWK_KERNEL_PROCESS_TSS_H
#define CSWK_KERNEL_PROCESS_TSS_H

#include <stdint.h>

extern flush_tss();

/*
 * Task State Segment
 *
 *  This OS uses software process switching, as it is both more portable and faster.
 *  However, a TSS is still required in order to be able to switch between Kernel and User mode
 *  Therefore, despite the amount of entries to the TSS most will not be used, the most important are ESP0 and SS0
 *
 *  Reference: https://wiki.osdev.org/Task_State_Segment
 * */
struct tss {
  uint32_t prev_tss; // The previous TSS - with hardware task switching these form a kind of backward linked list.
  uint32_t esp0;     // The stack pointer to load when changing to kernel mode.
  uint32_t ss0;      // The stack segment to load when changing to kernel mode.
  // Everything below here is unused.
  uint32_t esp1; // esp and ss 1 and 2 would be used when switching to rings 1 or 2.
  uint32_t ss1;
  uint32_t esp2;
  uint32_t ss2;
  uint32_t cr3;
  uint32_t eip;
  uint32_t eflags;
  uint32_t eax;
  uint32_t ecx;
  uint32_t edx;
  uint32_t ebx;
  uint32_t esp;
  uint32_t ebp;
  uint32_t esi;
  uint32_t edi;
  uint32_t es;
  uint32_t cs;
  uint32_t ss;
  uint32_t ds;
  uint32_t fs;
  uint32_t gs;
  uint32_t ldt;
  uint16_t trap;
  uint16_t iomap_base;
} __attribute__((packed));

typedef struct tss tss_entry_t;


#endif //CSWK_KERNEL_PROCESS_TSS_H
