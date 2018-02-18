//
// Created by Tooster on 17.02.2018.
//

// http://www.usaco.org/current/data/sol_cowjog_gold.html

#include "bits/stdc++.h"
using namespace std;

int main(){
    int n;
    long long t;
    scanf("%d %lld",&n, &t );


    vector<long long> A;
    for (int i = 0; i < n; i++) {
        long long x, s;
        scanf("%lld %lld", &x, &s);
        x = -(x + s * t);

        if (A.empty() || x >= A.back())
            A.push_back(x);
        else
            *upper_bound(A.begin(), A.end(), x) = x;
    }

    printf("%d", A.size());
    return 0;
}