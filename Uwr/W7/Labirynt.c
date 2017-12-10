//
// Created by Tooster on 10.12.2017.
//


#include <stdio.h>
#include "deque.h"

int n, m;

int tab[102][102];
//tttttxxxyyy
#define parseCords(time, x, y) ((time)*1000000+ (x)*1000 + (y))
#define getTime(cords) ((cords)/1000000)
#define getX(cords) (((cords)/1000)%1000)
#define getY(cords) ((cords)%1000)

void printLabirynt() {
    for (int i__ = 0; i__ < n + 2; i__++) {
        for (int j__ = 0; j__ < m + 2; j__++) {
            if (tab[i__][j__] == 0)
                printf("-");
            if (tab[i__][j__] == 1)
                printf("#");
            if (tab[i__][j__] == 2)
                printf("o");
        }
        printf("\n");
    }
    printf("=========\n");
}

void flood(deque *DQ, int *dry, int time, int i, int j) {
    if (tab[i][j] == 0) {
        tab[i][j] = 2;
        (*dry)--;
        deque_pushBack(DQ, parseCords(time, i, j));
    }
}

int main() {

    deque *DQ = deque_alloc();

    char buffer[110];
    scanf("%d %d ", &n, &m);
    //border
    for (int i = 0; i < 102; ++i)
        tab[i][0] = tab[i][m + 1] = tab[0][i] = tab[n + 1][i] = 1;
    //reading
    int dry = 0;
    for (int i = 1; i <= n; ++i) {
        fgets(buffer, sizeof(buffer), stdin);
        for (int j = 1; j <= m; ++j) {
            if (buffer[j - 1] == '-')
                dry++;
            else if (buffer[j - 1] == '#')
                tab[i][j] = 1;
            else if (buffer[j - 1] == '!') {
                tab[i][j] = 2;
                deque_pushBack(DQ, parseCords(0, i, j));
            }
        }
    }
    //printLabirynt(tab);

    int time = 0;
    while (!deque_isEmpty(DQ)) {
        long long cords = deque_popFront(DQ);
        int now = getTime(cords);
        int i = getX(cords);
        int j = getY(cords);
        flood(DQ, &dry, now + 1, i - 1, j);
        flood(DQ, &dry, now + 1, i + 1, j);
        flood(DQ, &dry, now + 1, i, j - 1);
        flood(DQ, &dry, now + 1, i, j + 1);
        time = now;
        //printLabirynt();
    }

    printf("%d", dry != 0 ? -1 : time);
    deque_front(DQ);
}
