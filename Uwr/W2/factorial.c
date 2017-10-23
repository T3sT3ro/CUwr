//
// Created by Tooster on 18.10.17.
//

// Maksymilian Polarczyk
// Lista 2
// Zadanie 2 - silnia
#include <stdio.h>

unsigned long long factorial(unsigned long long n) {
    if (n == 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    printf("Please, input an integer n in range 1-20\n");
    unsigned int n;
    while (1) {
        scanf("%u", &n);
        if (n > 20)
            printf("Input again\n");
        else {
            printf("%u! = %lld", n, factorial((unsigned long long) n));
            return 0;
        }
    }
}
