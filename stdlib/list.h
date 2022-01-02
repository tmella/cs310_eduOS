
#ifndef CSWK_STDLIB_LIST_H
#define CSWK_STDLIB_LIST_H

#include <stdint.h>

/* Generic queue element */
typedef struct list_elem {
  void *value;
  struct list_elem *next;
} list_elem;

typedef struct {
  uint32_t size;
  uint32_t alloc_size;
  list_elem *head;
} List;

List *init_list(uint32_t alloc_size);
void add_front(List *, void *val);
void add_back(List *lst, void *elem);

void *remove_at(List *lst, int index);

// perhaps we need a remove function, but for now we will just remove

#endif //CSWK_STDLIB_LIST_H
