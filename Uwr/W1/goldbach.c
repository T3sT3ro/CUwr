//
// Created by Tooster on 2017-10-12.
//

#include <stdio.h>
#include <stdbool.h>

bool isPrime(int p) {
    for (int i = 2; i * i <= p; ++i) {
        if (p % i == 0) {
            //fprintf(stderr, "i=%d\n", i);
            return false;
        }
    }
    return true;
}

int prime_ways(int n) {
    int ways = 0;
    for (int i = 2; i <= n / 2; ++i) {
        if (i <= n - i && isPrime(i) && isPrime(n - i))
            ways++;
    }
    return ways;
}

int goldbach_main() {
    int n;
    scanf("%d", &n);
    if (n > 2 && n % 2 == 0)
        printf("%d", prime_ways(n));
    else
        printf("NIEPOPRAWNA LICZBA");
    return 0;
}

