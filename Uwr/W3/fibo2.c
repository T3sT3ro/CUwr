#include <stdio.h>

#define LOWER_LIMIT 0
#define UPPER_LIMIT 92

long long F[UPPER_LIMIT + 1];

long long fibo(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (F[n] != 0) return F[n];
    if (F[n] == 0) F[n] = fibo(n - 1) + fibo(n - 2);
    return F[n];
}

int main() {

    int n = -1;
    while (n < LOWER_LIMIT || n > UPPER_LIMIT) {
        printf("Please input number in range [%d-%d] for n-th fibonacci number\n", LOWER_LIMIT, UPPER_LIMIT);
        scanf("%d", &n);
    }
    printf("Fibonacci_%d = %lld\n", n, fibo(n));
    return 0;
}
