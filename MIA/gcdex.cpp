//
// Created by Tooster on 17.02.2018.
//

// https://site.ada.edu.az/~medv/acm/Docs%20e-olimp/Volume%2013/1229_English.htm

#include "bits/stdc++.h"

using namespace std;

const int N = 1000006;
long long totient[N];
long long d[N];

void _totient() {
    for (int i = 2; i < N; ++i) totient[i] = i;
    for (int i = 2; i < N; i += 2) totient[i] /= 2;
    for (int i = 3; i < N; i += 2)
        if (totient[i] == i)
            for (int j = i; j < N; j += i)
                totient[j] -= totient[j] / i;
    for (int i = 0; i < N; ++i)
        d[i] = totient[i];
}

void _f() {
    for (long long i = 2; i*i < N; ++i) {
        d[i * i] += i * totient[i];
        for (long long j = i * i + i, k = i + 1; j < N; j += i, k++)
            d[j] += i * totient[k] + k * totient[i];

    }

    for (int i = 3; i < N; ++i)
        d[i] += d[i - 1];
}

int main() {

    _totient();
    _f();
    int n;
    scanf("%d", &n);
    while (n != 0) {
        printf("%lld\n", d[n]);
        scanf("%d", &n);
    }
    return 0;
}
