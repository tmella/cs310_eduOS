
#include "list.h"
#include "../kernel/memory/heap.h"
#include "../kernel/kstdlib.h"

// should exclude this
// TODO should the list handle the k_malloc logic

#define null_ptr ((void *)0)

List *init_list(uint32_t alloc_size) {
    List *lst = k_malloc(sizeof(List));

    lst->alloc_size = alloc_size;
    lst->head = null_ptr;
    lst->size = 0;

    return lst;
}

void add_front(List *lst, void *elem) {
    list_elem *new_elem = k_malloc(sizeof(list_elem));
    new_elem->value = elem;
    new_elem->next = lst->head;
    lst->head = new_elem;

    lst->size++;
}

list_elem *get_tail(List *lst) {
    list_elem *iter = lst->head;
    if(!iter)
        return null_ptr;

    while(iter->next)
        iter = iter->next;

    return iter;
}

void add_back(List *lst, void *elem) {
    list_elem *new_elem = k_malloc(sizeof(list_elem));
    new_elem->value = elem;
    new_elem->next = null_ptr;

    if(lst->size == 0) {
        lst->head = new_elem;
    } else {
        list_elem *last = get_tail(lst);
        last->next = new_elem;
    }
    lst->size++;
}

list_elem *get_at_index(List *lst, int index) {
    list_elem *iter = lst->head;
    int iteration = 0;
    while(iter->next && iteration < index) {
        iteration++;
        iter = iter->next;
    }
    return iter;
}

void *remove_at(List *lst, int index) {
    if(index >= lst->size) {
        // FIXME PANIC SHOULDNT HAPPEN
        return null_ptr;
    }

    lst->size--;

    if(index == 0) {
        list_elem *actual_elem = lst->head;
        void *val_to_free = actual_elem->value;
        lst->head = lst->head->next;
        k_free(actual_elem);
        return val_to_free;
    }

    list_elem *prev_elem = get_at_index(lst, index - 1);
    list_elem *actual_elem = prev_elem->next;
    void *val_to_free = actual_elem->value;

    prev_elem->next = prev_elem->next->next;

    k_free(actual_elem);
    return val_to_free;
}
