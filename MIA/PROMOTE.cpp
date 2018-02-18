//
// Created by Tooster on 12.02.2018.
//

#include <bits/stdc++.h>
#include <numeric>

using namespace std;

const int N = 100005;
const int off = 1 << 17;

int prod[N];
pair<int, int> cowRange[N]; // has conrol over cows in range [a,b]
vector<int> tree[N];
int BST[2 * off]; // array for BST
vector<int> cowsByProd; // cows sorted by decreasing productivity
int ret[N]; // array of results

int n, t = -1;

void calcTimes(int node) {
    cowRange[node].first = ++t;
    for (int i = 0; i < tree[node].size(); ++i)
        calcTimes(tree[node][i]);
    cowRange[node].second = t+1;
}

bool comp(int lhs, int rhs) {
    return prod[lhs] > prod[rhs];
}

void update(int cow) {
    int it = cowRange[cow].first + off;
    BST[it]++;
    while (it /= 2)
        BST[it]++;
}

int _get(int v, int a, int b, int lo, int hi) {
    if (a == lo && b == hi)
        return BST[v];
    if (b <= a) return 0;
    int mid = (lo + hi) / 2;
    return _get(v * 2, a, min(b, mid), lo, mid) +
           _get(v * 2 + 1, max(a, mid), b, mid, hi);
}

int get(int cow) {
    return _get(1, cowRange[cow].first, cowRange[cow].second, 0, off);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &prod[i]);
    for (int i = 2; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        tree[x].push_back(i);
    }
    calcTimes(1);
    for (int i = 1; i <= n; ++i)
        cowsByProd.push_back(i);
    sort(cowsByProd.begin(), cowsByProd.end(), comp);

    for (int i = 0; i < cowsByProd.size(); ++i) {
        ret[cowsByProd[i]] = get(cowsByProd[i]);
        update(cowsByProd[i]);
    }

    for (int i = 0; i < n; ++i)
        printf("%d ", ret[i+1]);
    return 0;
}