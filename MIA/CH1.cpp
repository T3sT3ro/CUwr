//
// Created by Tooster on 17.02.2018.
//


#include "bits/stdc++.h"

#define x first
#define y second

using namespace std;

typedef pair<long long, long long> Point;

/// <0 Left   =0 on   >0 Right
int side(Point checked, Point vec_begin, Point vec_end) {
    long long ret = (checked.x - vec_begin.x) * (vec_end.y - vec_begin.y) -
                    (checked.y - vec_begin.y) * (vec_end.x - vec_begin.x);
    return (0 < ret) - (ret < 0); //signum
}

void _f() {

    vector<Point> V;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        long long a, b;
        scanf("%lld %lld", &a, &b);
        V.push_back(make_pair(a, b));
    }
    vector<Point> CH(V.size() * 2);
    sort(V.begin(), V.end());
    int it = 0;
    for (int i = 0; i < n; ++i) {
        while (it >= 2 && side(V[i], CH[it - 2], CH[it - 1]) >= 0)
            it--;
        CH[it++] = V[i];
    }

    for (int i = n - 2, it2 = it + 1; i >= 0; --i) {
        while (it >= it2 && side(V[i], CH[it - 2], CH[it - 1]) >= 0)
            it--;
        CH[it++] = V[i];
    }
    CH.resize(it - 1);
    for (int i = 0; i < CH.size(); ++i) {
        printf("%d %d\n", (int) CH[i].first, (int) (CH[i].second));
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        printf("Case #%d\n", i);
        _f();
    }
}