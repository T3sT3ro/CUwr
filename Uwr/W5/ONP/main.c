//
// Created by i300791 on 22.11.17.
//
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "wyrazenie.h"

#define MAXBUFFER 300

int main() {

    printf("Wpisz wyrazenie ONP skladajace sie z liczb i symboli {+,-,*,/,%%,m (minimum),M (Maximum)}\n");
    printf("Liczby i symbole powinny byc oddzielone pojedynczymi spacjami.\n");
    printf("Wyrazenie zatwierdz znakiem nowej linii.\n");
    printf("Aby zakonczyc, wpisz 'x'.\n");
    char *input = malloc(MAXBUFFER);
    while (true) {
        /*
         * Wczytywanie linii i sprawdzenie symboli
         */
        fgets(input, MAXBUFFER, stdin);
        if (input[0] == 'x')
            break;
        struct wyrazenie *w = wyrazenie_alloc();
        wyrazenie_init(w, input);
        printf("= %d\n", wyrazenie_oblicz(w));
        wyrazenie_free(w);
    }
    return 0;
}
