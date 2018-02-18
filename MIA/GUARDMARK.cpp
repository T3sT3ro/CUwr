//
// Created by Tooster on 15.02.2018.
//

//http://codeforces.com/blog/entry/15188
#include "bits/stdc++.h"

using namespace std;

long long DP[1100000], He[1100000];

struct Cow {
    long long w, s, h;

    Cow(long long int w, long long int s, long long int h) : w(w), s(s), h(h) {}
};

vector<Cow> V;

int main() {
    int n;
    long long H;
    scanf("%d %lld", &n, &H);
    for (int i = 0; i < n; ++i) {
        long long h, w, s;
        scanf("%lld %lld %lld", &h, &w, &s);
        V.push_back(Cow(w, s, h));
    }

    long long ans = -1;
    DP[0] = LONG_LONG_MAX;

    for (int i = 0; i < 1 << n; ++i) DP[i] = LONG_LONG_MIN;
    for (int mask = 0; mask < 1 << n; ++mask) {

        if (He[mask] >= H) ans = max(ans, DP[mask]);
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) {
                long long next_dp = min(DP[mask] - V[i].w, V[i].s);
                long long next_h = He[mask] + V[i].h;
                long long next_mask = mask + (1 << i);
                He[next_mask] = next_h;
                DP[next_mask] = max(DP[next_mask], next_dp);
            }
        }
    }

    if (ans >= 0)
        printf("%lld", ans);
    else
        printf("Mark is too tall");

    return 0;
}
