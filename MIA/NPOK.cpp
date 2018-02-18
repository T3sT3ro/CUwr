//
// Created by Tooster on 14.02.2018.
//

//http://fishi.devtail.io/weblog/2015/06/25/computing-large-binomial-coefficients-modulo-prime-non-prime/

#include "bits/stdc++.h"

// b^e %mod
long long mod_exp(long long b, long long e, long long mod) {
    long long r = 1;
    while (e > 0) {
        if (e & 1)
            r = (r * b) % mod;
        b = (b * b) % mod;
        e >>= 1;
    }
    return r;
}

void _f() {
    long long n, k, p;
    scanf("%lld %lld %lld", &n, &k, &p);


    long long num = 1;
    for (long long i = n; i > n - k; --i)
        num = (num * i) % p;

    long long denom = 1;
    for (long long i = 1; i <= k; ++i)
        denom = (denom * i) % p;

    printf("%lld\n", (num * mod_exp(denom, p - 2, p)) % p);
}

int main() {
    int N;
    scanf("%d", &N);
    while (N--)
        _f();
    return 0;
}
