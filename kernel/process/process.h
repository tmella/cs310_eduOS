
#ifndef CSWK_KERNEL_PROCESS_PROCESS_H
#define CSWK_KERNEL_PROCESS_PROCESS_H

#include "stdint.h"

// States of a process
#define NEW_STATE 0 // The process is being created
#define READY_STATE 1 // The processor is waiting to be assinged to a processor
#define RUNNING_STATE 2 // The process is executing
#define WAITING_STATE 3 // The process is waiting for an event to occurr
#define TERMINATED_STATE 4 // The process has finished


/* These registers are architecture specific */
struct x86_registers {
  // General purpose registers
  uint32_t edi, esi, ebx, edx, ecx, eax;
  // Segment registers
  uint32_t ds, cs, ss, es, fs, gs;
  // Stack registers
  uint32_t esp, ebp;

  uint32_t eflags; // TODO: perhaps should be its own struct

  uint32_t eip; // Extended instruction pointer
};

typedef struct {
    uint32_t pid;
    uint8_t state;
    uint32_t program_counter;

    struct x86_registers reg;

    // Program text
    void (*text)();
} process_control_block;


#endif //CSWK_KERNEL_PROCESS_PROCESS_H
