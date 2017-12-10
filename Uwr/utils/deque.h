//
// Created by Tooster on 22.11.2017.
//

#ifndef CUWR_STACK_H
#define CUWR_STACK_H


#include <stdbool.h>

typedef struct deque_struct deque;
typedef struct node_struct node;
typedef long long deque_TYPE;


deque *deque_alloc();

void deque_free(deque *d);

bool deque_isEmpty(deque *d);

void deque_pushFront(deque *d, deque_TYPE val);

void deque_pushBack(deque *d, deque_TYPE val);

deque_TYPE deque_front(deque *d);

deque_TYPE deque_back(deque *d);

deque_TYPE deque_popFront(deque *d);

deque_TYPE deque_popBack(deque *d);

deque_TYPE deque_get(deque *d, int index);

#endif //CUWR_STACK_H
