
#include "queue.h"
#include <stddef.h>
#include "../stdlib/stdlib.h"

void init_queue(ProcessQueue *queue, int length) {
    queue->headIndex = -1;
    queue->tailIndex = -1;
}

void enqueue(ProcessQueue *queue, PCB *newProcess) {

    print_string("Enqueueing element \n");

    if(queue->headIndex == -1) {
        print_string("Have initialized the head\n");
        queue->headIndex++;
    }

    struct QueueElem *oldTail;

    if(!isEmpty(queue)) {
        oldTail = &(queue->elems[queue->tailIndex]);
    } else {
        print_string("\nThe queue was empty you dumb fuck\n");
    }

    struct QueueElem newTail = {newProcess, oldTail};

    int val = newTail.pcb->pid;
    char str[10];
    print_string(itoa(val, str, 10));

    queue->elems[++queue->tailIndex] = newTail;
}

// FIXME: not actually circular will break once 256 operations are performed
// should be made dynamic by then once we can allocate memory on the Kernel heap
PCB *dequeue(ProcessQueue *queue) {
    if(isEmpty(queue)) {
        return NULL;
    }

    // Reduce the index
    queue->headIndex--;

    struct QueueElem newHead = queue->elems[queue->headIndex];

    newHead.nextElem = NULL;

    queue->length--;

    return newHead.pcb;
}

int isEmpty(ProcessQueue *queue) {
    return queue->length == 0; // Is this redundant in c?
}