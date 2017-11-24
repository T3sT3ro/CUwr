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

/**
 * Alokuje nowy stos w pamieci
 * @return wskaznik na nowy stos
 */
stack2 *stack2_alloc();

/**
 * Uwalnia pamiec przydzielona stosowi 's'
 * @param s stos do usuniecia
 */
void stack2_free(stack2 *s2);

/**
 * Sprawdza czy stos 's' jest pusty
 * @param s dany stos
 * @return true jesli nie zawiera elementow, false w przeciwnym wypadku
 */
bool stack2_isEmpty(stack2 *s2);

/**
 * Dodaje element val do stosu 's'
 * @param s stos, do ktorego dodac
 * @param val dodawany element
 */
void stack2_push(stack2 *s2, STACK2_TYPE val);

/**
 * Zwraca element ze szczytu stosu 's'
 * @param s stos
 * @return element na szczycie stosu
 */
STACK2_TYPE stack2_top(stack2 *s2);

/**
 * Usuwa element ze szczytu stosu 's' i zwraca go
 * @param s stos
 * @return element ze szczytu stosu
 */
STACK2_TYPE stack2_pop(stack2 *s2);

#endif //CUWR_TABLE_STACK_H
