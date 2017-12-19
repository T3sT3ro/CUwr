//
// Created by Tooster on 19.12.2017.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node_ node;

struct node_ {
    node *L;
    node *R;
    int size;
    bool inner;
    char c;
};

int howMany[128];
node *t[128];

int cmp(const void *a, const void *b) {
    node *_a = *(node **) a;
    node *_b = *(node **) b;
    if ((_a)->size < (_b)->size) return -1;
    if ((_a)->size == (_b)->size) return 0;
    return 1;
}

int DFS(node *n, int st) {
    if (n->inner)
        return DFS(n->L, st + 1) + DFS(n->R, st + 1);
    return st * n->size;
}

int main() {

    for (int i = 0; i < 128; ++i) {
        howMany[i] = 0;
        t[i] = NULL;
    }

    char c;
    c = getchar();

    int it = 0;
    while (c != EOF) {
        if (howMany[(int) c] == 0) {
            node *n = malloc(sizeof(node));
            n->L = NULL;
            n->R = NULL;
            n->inner = false;
            n->c = c;
            t[it++] = n;
        }
        howMany[(int) c]++;
        c = getchar();
    }

    for (int j = 0; j < it; ++j)
        t[j]->size = howMany[(int) t[j]->c];

    int nodes = it;
    if (it == 1) {
        printf("%d", howMany[(int) t[0]->c]);
        return 0;
    }
    int starting = 0;
    while (nodes > 1) {
        qsort(t + starting, nodes, sizeof(node *), cmp);
        node *a = t[starting];
        node *b = t[starting + 1];
        node *new = malloc(sizeof(node));
        new->L = a;
        new->R = b;
        new->size = a->size + b->size;
        new->inner = true;
        t[starting] = NULL;
        t[++starting] = new;
        nodes--;
    }

    printf("%d", DFS(t[starting], 0));

    return 0;
}