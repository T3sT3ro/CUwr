//
// Created by i300791 on 22.11.17.
//

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "wyrazenie.h"

#define min(a, b) (((a)<(b)) ? (a) : (b));
#define max(a, b) (((a)>(b)) ? (a) : (b));
#define abs(a) ((a)<0 ? (a)*(-1) : (a))

struct wyrazenie *wyrazenie_alloc() {
    struct wyrazenie *w = malloc(sizeof(struct wyrazenie));
    return w;
}

void wyrazenie_free(struct wyrazenie *w) {
    stack2_free(w->stos);
    free(w);
}

void wyrazenie_init(struct wyrazenie *w, char *string) {
    unsigned int length = 0;
    while (string[length++] != '\n');
    stack2 *stos = stack2_alloc();
    assert(stos != NULL);
    w->stos = stos;
    w->string = string;
    w->length = length;
}

int wyrazenie_oblicz(struct wyrazenie *w) {

    int wynik = 0;
    for (int i = 0; i < w->length; ++i) {
        if (isdigit(w->string[i]) ||
            (w->string[i] == '-' && isdigit(w->string[i + 1]))) { /// jesli to cyfra, dodaj do wyniku
            wynik = atoi(&(w->string[i]));
            //przesuwa i o tyle ile jest log10(wynik)
            int log10 = abs(wynik);
            while (log10 >= 10) {
                log10 /= 10;
                i++;
            }
            if (wynik < 0)
                i++;
        } else if (isspace(w->string[i])) { /// dodaje wynik na stos jak jest whitespace
            stack2_push(w->stos, wynik);
            wynik = 0;
        } else { /// Liczy dla osobnych operacji
            int arg[2];
            assert(arg != NULL);
            /*
             * Sciaga 2 wyniki ze stosu
             */
            for (int j = 0; j < 2; ++j) {
                if (stack2_isEmpty(w->stos)) {
                    printf("Blad wyrazenia ONP\n");
                    return 0;
                }
                arg[j] = stack2_pop(w->stos);

            }

            /*
             * Oblicza arg1 <op> arg2
             */
            if (w->string[i] == '+')
                wynik = arg[1] + arg[0];
            if (w->string[i] == '-')
                wynik = arg[1] - arg[0];
            if (w->string[i] == '*')
                wynik = arg[1] * arg[0];
            if (w->string[i] == '/') // Mozna doklepac blad jesli dzielenie przez 0 - domyslnie sie wykrzacza
                wynik = arg[1] / arg[0];
            if (w->string[i] == '%')
                wynik = arg[1] % arg[0];
            if (w->string[i] == 'M')
                wynik = max(arg[1], arg[0]);
            if (w->string[i] == 'm')
                wynik = min(arg[1], arg[0]);
        }
    }
    int ret = stack2_pop(w->stos);
    if (!stack2_isEmpty(w->stos)) {
        printf("Blad wyrazenia ONP\n");
        return 0;
    }
    return ret;

}

/**
 * wyr_init zwraca pointer na nowe wyrazenie
 * kazde wyrazenie zawiera swoj stos i stringa z sizem
 */