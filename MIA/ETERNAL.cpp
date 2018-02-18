//
// Created by Tooster on 15.02.2018.
//

#include "bits/stdc++.h"

int last[10][5] = {
        {1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 2, 4, 8, 6},
        {1, 3, 9, 7, 1},
        {1, 4, 6, 4, 6},
        {1, 5, 5, 5, 5},
        {1, 6, 6, 6, 6},
        {1, 7, 9, 3, 1},
        {1, 8, 4, 2, 6},
        {1, 9, 1, 9, 1}
};

int main() {
    long long a, b;
    scanf("%lld %lld", &a, &b);
    if(b==0){
        printf("%lld", b == 0 ? 1 : b%10);
        return 0;
    }
    long long ret = 1;
    for (int i = 0; i < 10; ++i) {
        long long times = (b / 10 + (i <= b % 10 ? 1 : 0)) - (a / 10 + (i <= a % 10 ? 1 : 0));
        if (times != 0) times = ((times-1) % 4) + 1;
        ret*=last[i][times];
    }
    printf("%lld", ret%10);
    return 0;
}