//
// Created by Tooster on 23.10.2017.
//

#include <iostream>

using namespace std;

const int limit = 1 << 20;
const int offset = 1 << 19;
int zera[limit];
int minusy[limit];
int V[offset];

int n, k;

void update(int x, int y) {
    int _zero = 0, _minus = 0;
    if (V[x] < 0 && y >= 0)
        _minus = -1;
    if (V[x] >= 0 && y < 0)
        _minus = 1;
    if (V[x] == 0 && y != 0)
        _zero = -1;
    if (V[x] != 0 && y == 0)
        _zero = 1;
    V[x] = y;
    int it = offset + x;
    do {
        minusy[it] += _minus;
        zera[it] += _zero;
        it /= 2;
    } while (it > 0);
}

int zlicz(int *tab, int a, int b) {
    a += offset;
    b += offset;
    if (a == b)
        return tab[a];
    int ile = tab[a] + tab[b];
    while (a / 2 != b / 2) {
        if (a % 2 == 0)
            ile += tab[a + 1];
        if (b % 2 == 1)
            ile += tab[b - 1];
        a /= 2;
        b /= 2;
    }
    return ile;
}

int main() {
    ios_base::sync_with_stdio(false);
    while (!(cin >> n).eof()) {
        cin >> k;
        for (int i = 0; i < limit; i++)
            zera[i] = minusy[i] = 0;
        for (int i = 0; i < offset; i++)
            V[i] = 0;
        for (int i = 1; i <= n; i++) {
            cin >> V[i];
            if (V[i] < 0) minusy[offset + i] = 1;
            if (V[i] == 0) zera[offset + i] = 1;
        }
        for (int i = limit - 1; i > 0; --i) {
            minusy[i / 2] += minusy[i];
            zera[i / 2] += zera[i];
        }
        while (k--) {
            char c;
            int x, y;
            cin >> c >> x >> y;
            if (c == 'C')
                update(x, y);
            else if (c == 'P') {
                if (zlicz(zera, x, y) > 0)
                    cout << '0';
                else if (zlicz(minusy, x, y) % 2 == 1)
                    cout << '-';
                else
                    cout << '+';
            }
        }
        cout << '\n';
    }
    return 0;
}