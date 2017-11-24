//
// Created by Tooster on 22.11.2017.
//

/**
 * Implementacja stosu oparta na liscie jednokierunkowej
 */

#ifndef CUWR_STACK_H
#define CUWR_STACK_H


#include <stdbool.h>

typedef struct stack_struct stack;
typedef int stack_TYPE;

/**
 * Alokuje nowy stos w pamieci
 * @return wskaznik na nowy stos
 */
stack *stack_alloc();

/**
 * Uwalnia pamiec przydzielona stosowi s
 * @param s stos do usuniecia
 */
void stack_free(stack *s);

/**
 * Sprawdza czy stos jest pusty
 * @param s dany stos
 * @return true jesli nie zawiera elementow, false w przeciwnym wypadku
 */
bool stack_isEmpty(stack *s);

/**
 * Dodaje element val to stosu s
 * @param s stos, do ktorego dodac
 * @param val dodawany element
 */
void stack_push(stack *s, stack_TYPE val);

stack_TYPE stack_top(stack *s);

stack_TYPE stack_pop(stack *s);

#endif //CUWR_STACK_H
