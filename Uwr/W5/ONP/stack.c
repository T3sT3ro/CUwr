//
// Created by Tooster on 22.11.2017.
//

#include <malloc.h>
#include <assert.h>
#include "stack.h"

struct node {
    struct node *prev;
    struct node *next;
    stack_TYPE val;
};

struct stack_struct {
    unsigned int size;
    struct node *begin;
    struct node *end;
};

stack *stack_alloc() {
    stack *s = malloc(sizeof(stack));
    if (s == NULL) // alloc error
        return NULL;
    struct node *begin = malloc(sizeof(struct node));
    struct node *end = malloc(sizeof(struct node));
    if (begin == NULL || end == NULL)
        return NULL;
    s->size = 0;
    s->begin = begin;
    s->end = end;
    s->begin->prev = s->end->next = NULL;
    s->begin->next = s->end;
    s->end->prev = s->begin;
    return s;
}

void stack_free(stack *s) {
    struct node *removeNode = s->begin;
    struct node *nextRemoveNode;
    do {
        nextRemoveNode = removeNode->next;
        free(removeNode);
        removeNode = nextRemoveNode;
    } while (removeNode != NULL);
    // zwalnia wszystkie Node-y
    free(s); // zwalnia sam stack
}

bool stack_isEmpty(stack *s) {
    return s->size == 0;
}

void stack_push(stack *s, stack_TYPE val) {
    struct node *n = malloc(sizeof(struct node));
    assert(n != NULL);
    n->val = val;
    n->prev = s->begin;
    n->next = s->begin->next;
    n->prev->next = n;
    n->next->prev = n;
    s->size++;
}

stack_TYPE stack_top(stack *s) {
    return s->size == 0 ? 0 : s->begin->next->val;
}

stack_TYPE stack_pop(stack *s) {
    if (s->size == 0)
        return 0;

    struct node *removed = s->begin->next;
    stack_TYPE ret = removed->val;
    // begin -> A -> B -> end
    removed->prev->next = removed->next; // przepina begin.next na B
    removed->next->prev = removed->prev; // ustawia B.prev na begin

    free(removed); // zwalnia A
    s->size--;
    return ret;
}