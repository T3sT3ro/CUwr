//
// Created by Tooster on 13.02.2018.
//
#include "bits/stdc++.h"

using namespace std;

const int D = 1000006, N = 20004;
const int off = 1 << 20;
int d;

pair<int, int> BST[2 * off]; // type set range, max on range, <max, ass>

void update(int v, int a, int b, int lo, int hi, int val) {
    if (a == lo && b == hi) {
        BST[v].second = val;
        BST[v].first = max(BST[v].first, BST[v].second);
        return;
    }
    if (b <= a) return;
    int mid = (lo + hi) / 2;
    update(v * 2, a, min(mid, b), lo, mid, val);
    update(v * 2 + 1, max(a, mid), b, mid, hi, val);
    BST[v].first = max(BST[v].first, max(BST[v * 2].first, BST[v * 2 + 1].first));
}


int get_max(int v, int a, int b, int lo, int hi) {
    if (a == lo && b == hi)
        return max(BST[v].first, BST[v].second);
    if (b <= a) return -1;
    int mid = (lo + hi) / 2;
    return max(BST[v].second,
               max(get_max(v * 2, a, min(mid, b), lo, mid),
                   get_max(v * 2 + 1, max(a, mid), b, mid, hi)));

}

int main() {
    int n;
    scanf("%d %d", &d, &n);
    while (n--) {
        int l, x;
        scanf("%d %d", &l, &x);
        update(1, x, x + l, 0, off, get_max(1, x, x + l, 0, off) + 1);
    }
    printf("%d", get_max(1, 0, d, 0, off));
    return 0;
}