//
// Created by Tooster on 13.11.2017.
//

#include <stdio.h>

#define min(a, b) (((a) > (b)) ? (b) : (a))

int rozklad[20][200]; //rozklad[przystanek p][czas odjazdu k w minutach];
int odjazdy[20];
int czas[20];

int main() {
    int przystanki;

    scanf("%d", &przystanki);
    for (int i = 0; i < przystanki; ++i) {
        scanf("%d %d", &czas[i], &odjazdy[i]);
        for (int j = 0; j < odjazdy[i]; ++j) {
            int hh, mm;
            scanf("%d %d", &hh, &mm);
            rozklad[i][j] = 60 * hh + mm;
        }
    }

    int minStart = rozklad[0][odjazdy[0] - 1];
    int minCzas = 2147483647;

    for (int i = 0; i < odjazdy[0]; ++i) { // po odjazdach z przystanku startowego
        int start = rozklad[0][i];
        int czasJazdy = 0;
        int czasDojechania = start;
        for (int j = 0; j < przystanki; ++j) { // dla każdego przystanku znajduje najmniejszy mniejszy równy przyjazdowi
            int najszybszy = czasDojechania;
            for (int k = 0; k < odjazdy[j]; ++k) { // znajduje pierwszy większy równy czasowi dojechania
                if (czasDojechania <= rozklad[j][k]) {
                    najszybszy = rozklad[j][k];
                    goto a;
                }
            }
            najszybszy = rozklad[j][0];
            a:
            czasJazdy += ((najszybszy - czasDojechania < 0) ?
                          24 * 60 - czasDojechania + najszybszy :
                          najszybszy - czasDojechania) + czas[j];
            czasDojechania = (najszybszy + czas[j]) % (24 * 60);
        }
        if (czasJazdy < minCzas) {
            minStart = start;
            minCzas = czasJazdy;
        }
    }

    printf("%d %d %d %d", minStart / 60, minStart % 60, minCzas / 60, minCzas % 60);
    return 0;
}