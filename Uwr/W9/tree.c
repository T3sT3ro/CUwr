//
// Created by Tooster on 02.01.2018.
//

#include <stdio.h>

int t[101];

int main() {
    for (int i = 0; i < 101; ++i)
        t[i] = i;
    int n;
    scanf("%d", &n);
    while (n--) {
        char op;
        int v, parent;
        scanf(" %c %d %d", &op, &v, &parent);
        t[v] = parent;
    }
    int d = 1, cv = 2;
    while (cv != t[cv]) {
        cv = t[cv];
        d++;
    }
    printf("%d", d);
    return 0;
}