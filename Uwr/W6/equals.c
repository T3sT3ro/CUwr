//
// Created by i300791 on 29.11.17.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/// zwraca tablice o n+1 elementach
/// t[0] oznacza ilosc argumentow
/// t[1..n] argumenty w ktorych funkcje sa rowne
int *equals(int (*f1)(int), int (*f2)(int), int a, int b) {

    int *args = calloc(b - a + 2, sizeof(int)); //elements, args[0] holds iterator and size
    memset(args, 0, (b - a + 2) * sizeof(int)); // fill 0
    for (int i = a; i <= b; ++i)
        if (f1(i) == f2(i))
            args[++args[0]] = i;

    return args;
}

// y = 2x+12
int l1(int x) {
    return 2 * x + 12;
}

// y = 6x
int l2(int x) {
    return 6 * x;
}

// y = 2x
int l3(int x) {
    return 2 * x;
}

// y = 4x + 1
int l4(int x) {
    return 4 * x + 1;
}

// y = x^2
int p1(int x) {
    return x * x;
}

// y = x^3 + 1
int w1(int x) {
    return x * x * x + 1;
}

void printArguments(int (*f1)(int), int (*f2)(int), int a, int b) {
    int *args = equals(f1, f2, a, b);
    for (int i = 0; i < args[0]; ++i)
        printf("%d ", args[i + 1]);
    printf("\n");
}

int main() {

    printArguments(l1, l2, -10, 10);
    printArguments(l1, l1, -10, 10);
    printArguments(l3, p1, -100, 100);
    printArguments(l4, w1, -100, 100);

    return 0;
}