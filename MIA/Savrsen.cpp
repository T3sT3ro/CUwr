//
// Created by Tooster on 06.11.2017.
//

#include <cstdio>
#include <cmath>

using namespace std;

const int M = 1000006;
int tab[M];

typedef long long ll;

int main() {
    for (int i = 2; i < M; i++)
        tab[i] = i - 1;

    int A, B;
    scanf("%d %d", &A, &B);


    tab[1] = 1;
    for (int i = 2; i < B; i++) {
        for (int j = 2 * i; j <= B; j += i) {
            tab[j] -= i;
        }
    }
    ll sum = 0;
    for (int i = A; i <= B; i++)
        sum += abs(tab[i]);
    printf("%lld", sum);

    return 0;
}