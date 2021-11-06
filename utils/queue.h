

#ifndef CSWK_UTILS_QUEUE_H
#define CSWK_UTILS_QUEUE_H

#include "../kernel/process.h"

struct QueueElem {
  struct PCB* pcb;

  struct QueueElem* nextElem;
};

typedef struct Queue {
  unsigned int length;
   int headIndex;
  int tailIndex;
  struct QueueElem elems[256];
} ProcessQueue;


// NOTHING YET BECAUSE OF SHIT IMPLEMENTATION
void init_queue(ProcessQueue *queue, int length);

void enqueue(ProcessQueue *queue, PCB *newProcess);
PCB* dequeue(ProcessQueue *queue);

int isEmpty(ProcessQueue *queue);



#endif //CSWK_UTILS_QUEUE_H
