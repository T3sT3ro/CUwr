//
// Created by Tooster on 15.02.2018.
//
#include "bits/stdc++.h"

using namespace std;

const int N = 1003;
bool edge[N][N];
int clicked[N];

int n, k;

inline bool is_wrong() {

    for (int i = 1; i <= n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            int to_set = edge[i][j] ?
                         (clicked[i] == 2 ? 2 : 1) :
                         (clicked[i] == 2 ? 1 : 2);
            assert(clicked[i] != 0);
            if (clicked[j] == 0)
                clicked[j] = to_set;
            else if (to_set != clicked[j])
                return true;
        }
    }
    return false;
}

int main() {

    scanf("%d %d", &n, &k);
    for (int i = 0; i < k; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b) swap(a, b);
        edge[a][b] = true;
    }

    bool wrong = false;
    clicked[1] = 1; // assume clicked
    wrong = is_wrong();
    if (!wrong) {
        for (int j = 0; j < N; ++j) // reset clicked
            clicked[j] = 0;
        clicked[1] = 2; // assume not clicked
        wrong = is_wrong();
    }

    printf(wrong ? "NE" : "DA");
    return 0;
}