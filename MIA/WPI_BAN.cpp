//
// Created by Tooster on 14.02.2018.
//

#include "bits/stdc++.h"

using namespace std;

void _f() {
    int n;
    long long S;
    scanf("%d %lld", &n, &S);
    stack<long long> STACK;
    map<long long, int> MAP;
    long long envelopes = 0;

    while (n--) {
        long long x;
        scanf("%lld", &x);
        if (x > 0) { // deposit
            STACK.push(x);
            MAP[x]++;
            envelopes += x;
        } else { // withdraw
            if (STACK.empty() || abs(x) < MAP.begin()->first){ // no envelopes or less than min in envelopes
                S += x;
            } else {
                while (x < 0 && !STACK.empty()) {
                    long long drawn = STACK.top();
                    envelopes -= drawn;
                    STACK.pop();
                    if ((--MAP[drawn]) == 0)
                        MAP.erase(drawn);
                    x += drawn;
                }
                if (x != 0) // to few or to much money
                    S += x;
            }
        }
    }
    printf("%lld %lld\n", S, envelopes);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--)
        _f();
    return 0;
}