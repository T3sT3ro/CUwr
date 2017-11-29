//
// Created by i300791 on 29.11.17.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int l1(int x) {
    return 2 * x + 12;
}

int l2(int x) {
    return 6 * x;
}

/// zwraca tablice o n+1 elementach
/// t[0] oznacza ilosc argumentow
/// t[1..n] argumenty w ktorych funkcje sa rowne
int *equals(int (*f1)(int), int (*f2)(int), int a, int b) {
    
    int *args = calloc(b-a+2, sizeof(int)); //elements, args[0] holds iterator and size
    memset(args, 0, (b-a+2)*sizeof(int)); // fill 0
    for (int i = a; i <= b; ++i)
        if(f1(i) == f2(i))
            args[++args[0]] = i;

    return args;
}

int main() {

    int *args = equals(l1, l2, -10, 10);
    for (int i = 0; i < args[0]; ++i)
        printf("%d ", args[i]);

    return 0;
}