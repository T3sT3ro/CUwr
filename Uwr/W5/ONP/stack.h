//
// Created by Tooster on 22.11.2017.
//

#ifndef CUWR_STACK_H
#define CUWR_STACK_H


#include <stdbool.h>

typedef struct stack_struct stack;
typedef int stack_TYPE;

stack *stack_alloc();

void stack_free(stack *s);

bool stack_isEmpty(stack *s);

void stack_push(stack *s, stack_TYPE val);

stack_TYPE stack_top(stack *s);

stack_TYPE stack_pop(stack *s);

#endif //CUWR_STACK_H
