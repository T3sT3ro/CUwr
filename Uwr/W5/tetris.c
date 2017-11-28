//
// Created by Tooster on 14.11.2017.
//

#include <stdio.h>
#include <stdbool.h>

bool tetris[1000][1000];

int w, h, k;

struct Figura {
    int w, h;
    bool *t[4];
};

bool K[2][2] = {{1, 1},
                {1, 1}};

bool T[2][3] = {{1, 1, 1},
                {0, 1, 0}};

bool I[4][1] = {{1},
                {1},
                {1},
                {1}};

bool F[3][2] = {{1, 1},
                {1, 0},
                {1, 0}};

bool W[3][5] = {{1, 0, 1, 0, 1},
                {1, 0, 1, 0, 1},
                {1, 1, 1, 1, 1}};

void gravity(int index, struct Figura f) {
    for (int i = 0; i < f.h; ++i)  // wywala jak jest bug z pojawieniem się figuy
        for (int j = 0; j < f.w; ++j)
            if (tetris[1 + i][index + j] == 1)
                return;

    int lvl = 1;
    for (; lvl <= h - f.h; ++lvl) {
        for (int i = 0; i < f.h; ++i) // spycha na dol figure
            for (int j = 0; j < f.w; ++j)
                if (f.t[i][j] == 1 && tetris[i + lvl + 1][index + j] == 1)
                    goto write;

    }
    write:
    for (int i = 0; i < f.h; ++i)  // wywala jak jest bug z pojawieniem się figuy
        for (int j = 0; j < f.w; ++j)
            if (f.t[i][j] == 1)
                tetris[i + lvl][index + j] = 1;

    /// override full rows with rows above;

    int looker = lvl + f.h - 1;
    int writer = looker;
    while (looker >= 1) {
        bool full = true;
        for (int i = 1; i <= w; ++i)
            if (tetris[looker][i] == 0) {
                full = false;
                break;
            }

        if (full) {
            looker--;
            continue;
        }
        if (looker != writer) { // przepisuje wiersz
            for (int i = 1; i <= w; ++i)
                tetris[writer][i] = tetris[looker][i];
        }
        looker--;
        writer--;
    }
}

void bomb(int index) {
    if (tetris[1][index] == 1)
        return;
    int lvl = 1;
    while (lvl < h && tetris[lvl + 1][index] == 0)
        lvl++;
    tetris[lvl - 1][index - 1] = tetris[lvl - 1][index] = tetris[lvl - 1][index + 1] = 0;
    tetris[lvl][index - 1] = tetris[lvl][index] = tetris[lvl][index + 1] = 0;
    tetris[lvl + 1][index - 1] = tetris[lvl + 1][index] = tetris[lvl + 1][index + 1] = 0;
}

int main() {
    scanf("%d %d %d", &w, &h, &k);
    while (k--) {
        char c;
        int x;
        scanf("\n%c %d", &c, &x);
        x++;
        struct Figura f;
        if (c == '*') {
            bomb(x);
        } else if (c == 'K') {
            f.w = 2, f.h = 2;
            f.t[0] = K[0];
            f.t[1] = K[1];
        } else if (c == 'T') {
            f.w = 3, f.h = 2;
            f.t[0] = T[0];
            f.t[1] = T[1];
        } else if (c == 'I') {
            f.w = 1, f.h = 4;
            f.t[0] = I[0];
            f.t[1] = I[1];
            f.t[2] = I[2];
            f.t[3] = I[3];
        } else if (c == 'F') {
            f.w = 2, f.h = 3;
            f.t[0] = F[0];
            f.t[1] = F[1];
            f.t[2] = F[2];
        } else if (c == 'W') {
            f.w = 5, f.h = 3;
            f.t[0] = W[0];
            f.t[1] = W[1];
            f.t[2] = W[2];
        }
        if (c != '*')
            gravity(x, f);
    }
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            printf("%c", tetris[i][j] ? 'X' : '.');
        }
        printf("\n");
    }
    return 0;
}