//
// Created by Tooster on 16.02.2018.
//

#include "bits/stdc++.h"

using namespace std;
const int N = 1000006;
pair<int, bool> R[N]; // <from which, by what>
queue<int> Q;

void get(int num) {
    if (num != 1)
        get(R[num].first);
    printf(R[num].second ? "1" : "0");
}

int main() {
    for (int i = 0; i < N; ++i)
        R[i] = make_pair(-1, 0);
    int n;
    scanf("%d", &n);
    if(n==1){
        printf("1");
        return 0;
    }
    R[1] = make_pair(1, 1);
    Q.push(1);
    bool zero_seen = false;
    while (!Q.empty() && !zero_seen) {
        int r = Q.front();
        Q.pop();
        for (int i = 0; i < 2; ++i) {
            int _r = (r * 10 + i) % n;
            if (R[_r].first == -1) { // not seen
                R[_r] = make_pair(r, i);
                Q.push(_r);
                if (_r == 0)
                    goto here;
            }
        }
    }
    here:
    get(0);

    return 0;
}

