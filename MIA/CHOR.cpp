#include <bits/stdc++.h>

//
// Created by Tooster on 13.02.2018.
//
const int R = 30, P = 13, N = 10, M = P;

int costs[P];
int mx[R];

using namespace std;

void _f() {
    int r, p, n, m;
    scanf("%d %d %d %d", &r, &p, &n, &m);

    int ingr_mask = 0; // maska składników
    for (int i = 0; i < m; ++i) {
        int in;
        scanf("%d", &in);
        ingr_mask |= (1 << in);
    }

    for (int i = 0; i < p; ++i)
        scanf("%d", &costs[i]);

    for (int i = 0; i < r; ++i) { // przepisy
        mx[i] = 0;
        for (int j = 0; j < p; ++j) {
            int in;
            scanf("%d", &in);
            mx[i] |= (in << j);
        }
    }
    int full_mask = (1 << p) - 1;

    int min_cost = INT_MAX;
    for (int buy_mask = 0; buy_mask <= full_mask; buy_mask++) {
        if (buy_mask & ingr_mask) continue; // bez posiadanych składników

        int can_make = 0;
        for (int i = 0; i < r; ++i)
            if (mx[i] == (mx[i] & (ingr_mask | buy_mask)))
                can_make++;

        if(buy_mask == 0b1111)
            ;

        if (can_make >= n) {
            int cost = 0;
            for (int i = 0; i < p; ++i) {
                if (buy_mask & (1 << i))
                    cost += costs[i];
            }
            min_cost = min(min_cost, cost);
        }
    }

    printf("%d\n", min_cost);
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--)
        _f();
    return 0;
}