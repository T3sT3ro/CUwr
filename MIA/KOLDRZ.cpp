//
// Created by Tooster on 15.02.2018.
//

#include "bits/stdc++.h"

using namespace std;
const int N = 500005;
vector<int> C;
stack<pair<int, int> > E;

int flag = 0;
pair<int, int> fstCand;
int cand = -1;

int main() {
    int n;
    scanf("%d", &n);
    C.resize(n + 1);
    for (int i = 0; i < n-1; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        E.push(make_pair(a, b));
    }
    for (int i = 0; i < n; ++i) {
        int c;
        scanf("%d", &c);
        C[i+1] = c;
    }
    while (!E.empty() && flag != 3) {
        pair<int, int> k = E.top();
        E.pop();
        if (C[k.first] != C[k.second]) { // edge from two different colors
            if (flag == 0) {
                fstCand = k;
                flag = 1;
            } else if (flag == 1) {
                if (k.first == fstCand.first || k.first == fstCand.second) {
                    cand = k.first;
                    flag = 2;
                } else if (k.second == fstCand.first || k.second == fstCand.second) {
                    cand = k.second;
                    flag = 2;
                } else
                    flag = 3;
            } else if (flag == 2) {
                if(k.first != cand && k.second != cand)
                    flag = 3;
            }
        }
    }
    printf(flag == 3 ? "NIE" : "TAK");
    return 0;
}