//
// Created by Tooster on 10.12.2017.
//

/**
 * Deque implementation with two dummy nodes
 * begin -> a=front -> b -> ... -> z=back -> end
 */

#include <malloc.h>
#include <assert.h>
#include "deque.h"

struct node_struct {
    node *prev;
    node *next;
    deque_TYPE val;
};

struct deque_struct {
    unsigned int size;
    node *begin;
    node *end;
};

deque *deque_alloc() {
    deque *d = malloc(sizeof(deque));
    if (d == NULL) // alloc error
        return NULL;
    node *begin = malloc(sizeof(node));
    node *end = malloc(sizeof(node));
    if (begin == NULL || end == NULL)
        return NULL;
    d->size = 0;
    d->begin = begin;
    d->end = end;
    d->begin->prev = d->end->next = NULL;
    d->begin->next = d->end;
    d->end->prev = d->begin;
    return d;
}

void deque_free(deque *d) {
    node *removeNode = d->begin;
    node *nextRemoveNode;
    do {
        nextRemoveNode = removeNode->next;
        free(removeNode);
        removeNode = nextRemoveNode;
    } while (removeNode != NULL);
    // zwalnia wszystkie Node-y
    free(d); // zwalnia sam deque
}

bool deque_isEmpty(deque *d) {
    return d->size == 0;
}

void deque_pushFront(deque *d, deque_TYPE val) {
    node *n = malloc(sizeof(node));
    assert(n != NULL);
    n->val = val;
    n->prev = d->begin;
    n->next = d->begin->next;
    n->prev->next = n;
    n->next->prev = n;
    d->size++;
}

void deque_pushBack(deque *d, deque_TYPE val) {
    node *n = malloc(sizeof(node));
    assert(n != NULL);
    n->val = val;
    n->next = d->end;
    n->prev = d->end->prev;
    n->prev->next = n;
    n->next->prev = n;
    d->size++;
}

deque_TYPE deque_front(deque *d) {
    return d->size == 0 ? 0 : d->begin->next->val;
}

deque_TYPE deque_back(deque *d) {
    return d->size == 0 ? 0 : d->end->prev->val;
}

deque_TYPE deque_popFront(deque *d) {
    if (d->size == 0)
        return 0;

    node *removed = d->begin->next;
    deque_TYPE ret = removed->val;
    // begin -> A -> B -> end
    removed->prev->next = removed->next; // przepina begin.next na B
    removed->next->prev = removed->prev; // ustawia B.prev na begin

    free(removed); // zwalnia A
    d->size--;
    return ret;
}

deque_TYPE deque_popBack(deque *d) {
    if (d->size == 0)
        return 0;

    node *removed = d->end->prev;
    deque_TYPE ret = removed->val;
    // begin -> A -> B -> end
    removed->prev->next = removed->next; // przepina begin.next na B
    removed->next->prev = removed->prev; // ustawia B.prev na begin

    free(removed); // zwalnia A
    d->size--;
    return ret;
}

deque_TYPE deque_get(deque *d, int index) {
    if (index < 0 || index >= d->size)
        return 0;
    node *current = d->begin->next;
    while (index--)
        current = current->next;

    return current->val;
}