
#ifndef CSWK_STDLIB_QUEUE_H
#define CSWK_STDLIB_QUEUE_H

#include <stdint.h>

/* Generic queue element */
typedef struct queue_elem {
  void *value;
  struct queue_elem *next;
} queue_elem;

typedef struct {
  uint32_t size;
  uint32_t alloc_size;
  queue_elem *head;
  queue_elem *tail;
} Queue;

Queue *init_queue(uint32_t elemSize);

void enqueue(Queue *queue, void *add);
void dequeue(Queue *queue, void *data);

int8_t is_empty(Queue *queue);

#endif //CSWK_STDLIB_QUEUE_H
