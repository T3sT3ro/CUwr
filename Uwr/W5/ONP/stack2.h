//
// Created by Tooster on 23.11.2017.
//

/**
 *  stack2 to inna implementacja stosu, oparta na dynamicznej tablicy
 *  (nie tak jak pierwotne stack, na liscie jednokieronkowej)
 */
#ifndef CUWR_TABLE_STACK_H
#define CUWR_TABLE_STACK_H

#include <stdbool.h>

#define INITIAL_CAPACITY 2

typedef struct stack2_struct stack2;
typedef int STACK2_TYPE;

stack2 *stack2_alloc();

void stack2_free(stack2 *s2);

bool stack2_isEmpty(stack2 *s2);

void stack2_push(stack2 *s2, STACK2_TYPE val);

STACK2_TYPE stack2_top(stack2 *s2);

STACK2_TYPE stack2_pop(stack2 *s2);

#endif //CUWR_TABLE_STACK_H
