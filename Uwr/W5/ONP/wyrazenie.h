//
// Created by i300791 on 22.11.17.
//


#ifndef CUWR_WYRAZENIE_H
#define CUWR_WYRAZENIE_H

#include "stack2.h"

struct wyrazenie {
    stack2 *stos;
    char *string;
    unsigned int length;
};

/**
 * Alokuje miejsce na nowe wyrazenie
 * @return wskaznik na nowe wyrazenie w pamieci
 */
struct wyrazenie *wyrazenie_alloc();

/**
 * Inicjalizuje wyrazenie 'w' z wejscia w formie stringa
 * @param w wyrazenie do zainicjalizowania
 * @param string string reprezentujacy wyrazenie ONP
 */
void wyrazenie_init(struct wyrazenie *w, char *string);

/**
 * Uwalnia pamiec zarezerwowana przez wyrazenie 'w'
 * @param w wyrazenie do usuniecia
 */
void wyrazenie_free(struct wyrazenie *w);

/**
 * Zwraca calkowity wynik wyrazenia ONP lub 0 i blad jesli wyrazenie jest niepoprawne
 * @param w wyrazenie do obliczenia
 * @return wynik wyrazenia ONP lub 0 i blad
 */
int wyrazenie_oblicz(struct wyrazenie *w);

#endif //CUWR_WYRAZENIE_H