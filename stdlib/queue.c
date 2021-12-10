
#include "../kernel/memory/heap.h"
#include "queue.h"
#include "stdlib.h"
#include "../drivers/screen.h"

#define null_ptr ((void *)0)

Queue *init_queue(uint32_t elemSize) {
    Queue *queue = (Queue *) k_malloc(sizeof(Queue));
    // TODO check if heap is full and/or failed ?
    queue->size = 0;
    queue->alloc_size = elemSize;
    queue->head = null_ptr;

    return queue;
}

// TODO: no error handling in place
void enqueue(Queue *queue, void *add) {
    queue_elem *new_elem = (queue_elem *) k_malloc(sizeof(queue_elem));

    // Create space on heap for element
    // Copy the data over
    new_elem->value = k_malloc(sizeof(queue->alloc_size));
    memset(add, new_elem->value, queue->alloc_size);

    new_elem->next = null_ptr;

    if (queue->size == 0) {
        queue->head = new_elem;
        queue->tail = new_elem;
        queue->head->next = queue->tail;
    } else {
        queue->tail->next = new_elem;
    }

    queue->size++;
}
void dequeue(Queue *queue, void *data) {
    if (queue->size == 0)
        return;

    queue_elem *old_head = queue->head;
    memset(old_head->value, data, queue->alloc_size);
    if (queue->size == 1) {
        queue->head = queue->tail = null_ptr;
    } else {
        queue->head = queue->head->next;
    }
    k_free(old_head->value);
    k_free(old_head);

    queue->size--;
}

int8_t is_empty(Queue *queue) {
    return queue->size;
}
