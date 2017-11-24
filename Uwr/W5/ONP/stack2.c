//
// Created by Tooster on 23.11.2017.in the army now
//

#include <malloc.h>
#include <stdio.h>
#include "stack2.h"

struct stack2_struct {
    unsigned int capacity;
    unsigned int size;
    STACK2_TYPE *tab;
};

stack2 *stack2_alloc() {
    stack2 *s2 = malloc(sizeof(stack2));
    if (s2 == NULL)
        return NULL;
    s2->capacity = INITIAL_CAPACITY;
    s2->size = 0;
    s2->tab = malloc(sizeof(STACK2_TYPE) * INITIAL_CAPACITY);
    if (s2->tab == NULL)
        return NULL;
    return s2;
}

void stack2_free(stack2 *s2) {
    free(s2->tab); // zwalnia tablice
    free(s2); // zwalnia sam stack
}

bool stack2_isEmpty(stack2 *s2) {
    return s2->size == 0;
}

void stack2_push(stack2 *s2, STACK2_TYPE val) {
    if (s2->size == s2->capacity) {
        s2->tab = realloc(s2->tab, sizeof(STACK2_TYPE) * (s2->capacity * 2));
        s2->capacity *= 2;
    }
    if (s2->tab == NULL) {
        printf("couldn't reallocate array!");
        return;
    }
    s2->tab[s2->size++] = val;
}

STACK2_TYPE stack2_top(stack2 *s2) {
    return s2->size == 0 ? 0 : s2->tab[s2->size - 1];
}

STACK2_TYPE stack2_pop(stack2 *s2) {
    if (s2->size == 0)
        return 0;
    STACK2_TYPE ret = stack2_top(s2);
    s2->size--;
    if (s2->capacity > INITIAL_CAPACITY)
        s2->tab = realloc(s2->tab, sizeof(STACK2_TYPE) * (--(s2->capacity)));
    if (s2->tab == NULL)
        return 0;
    return ret;
}