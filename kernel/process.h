
#ifndef CSWK_KERNEL_PROCESS_H
#define CSWK_KERNEL_PROCESS_H

#include "inter.h"

#define NEW_STATE 0 // The process is being created
#define READY_STATE 1 // The processor is waiting to be assinged to a processor
#define RUNNING_STATE 2 // The process is executing
#define WAITING_STATE 3 // The process is waiting for an event to occurr
#define TERMINATED_STATE 4 // The process has finished

typedef void (*process_text)();

enum state {
  _new,
  running,
  waiting,
  ready,
  terminated
};

// Process Control Block
// Stores all the information for a process
typedef struct PCB {
  int pid;
  int state;
  int program_counter;
  i_registers_t registers;
  unsigned int limit;
  // List of open files

  void (*text)();

} PCB;



#endif //CSWK_KERNEL_PROCESS_H
