#include <stdio.h>

#define LOWER_LIMIT 0
#define UPPER_LIMIT 92

long long fibo(long long n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibo(n - 1) + fibo(n - 2);
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
