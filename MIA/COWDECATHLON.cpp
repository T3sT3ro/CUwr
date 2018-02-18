//
// Created by Tooster on 17.02.2018.
//

//http://www.usaco.org/current/data/sol_dec.html

#include "bits/stdc++.h"

using namespace std;

typedef pair<int, int> Bonus;
#define lim first
#define pts second

const int N = 20, B = 20;

int skill[N][N];
vector<Bonus> bonuses[B];
int DP[1 << N];

int main() {
    int n, b;
    scanf("%d %d", &n, &b);
    for (int i = 0; i < b; ++i) {
        int e, l, p;
        scanf("%d %d %d", &e, &l, &p);
        bonuses[e - 1].push_back(Bonus(l, p));
    }
    for (int i = 0; i < N; ++i)
        sort(bonuses[i].begin(), bonuses[i].end());

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &skill[i][j]);


    for (int mask = 1; mask < (1 << n); ++mask) {
        int cows = __builtin_popcount(mask);
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                int points = DP[mask ^ (1 << j)] + skill[j][cows - 1];
                DP[mask] = max(DP[mask], points);
            }
        }
        for (int i = 0; i < bonuses[cows - 1].size(); i++) {
            if (DP[mask] < bonuses[cows - 1][i].lim)
                break;
            DP[mask] += bonuses[cows - 1][i].pts;
        }
    }

    printf("%d", DP[(1<<n)-1]);
    return 0;
}