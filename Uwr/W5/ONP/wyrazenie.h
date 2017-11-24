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

struct wyrazenie *wyrazenie_alloc();

void wyrazenie_free(struct wyrazenie *w);

void wyrazenie_init(struct wyrazenie *w, char *string);

int wyrazenie_oblicz(struct wyrazenie *w);

#endif //CUWR_WYRAZENIE_H