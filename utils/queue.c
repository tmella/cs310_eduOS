
#include "queue.h"
#include <stddef.h>
#include "../stdlib/stdlib.h"
#include "../drivers/screen.h"

void init_queue(ProcessQueue *queue, int length) {
    queue->headIndex = -1;
    queue->tailIndex = -1;
}

PCB *enqueue(ProcessQueue *queue, PCB newProcess) {
    if(queue->headIndex == -1)
        queue->headIndex++;

    struct QueueElem *oldTail;

    if(!isEmpty(queue)) {
        oldTail = &(queue->elems[queue->tailIndex]);
    }
    struct QueueElem newTail = {newProcess, oldTail};

    queue->elems[++queue->tailIndex] = newTail;

    queue->length++;

    return &queue->elems[queue->tailIndex].pcb;
}

// FIXME: not actually circular will break once 256 operations are performed
// should be made dynamic by then once we can allocate memory on the Kernel heap
PCB *dequeue(ProcessQueue *queue) {
    if(isEmpty(queue)) {
        print_string("Its null while dequeueing");
        return NULL;
    }

    int readlIndex = queue->headIndex;

    // Increase the index
    queue->headIndex++;

    // Update the pointer to the new head
    if(queue->headIndex != -1) {
        struct QueueElem newHead = queue->elems[queue->headIndex];
        newHead.nextElem = NULL;
    }

    queue->length--;

    return &queue->elems[readlIndex].pcb;
}

int isEmpty(ProcessQueue *queue) {
    return queue->length == 0; // Is this redundant in c?
}