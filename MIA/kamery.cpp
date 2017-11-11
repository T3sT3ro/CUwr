//
// Created by Tooster on 06.11.2017.
//

#include <string>
#include <cstdio>

using namespace std;

bool tab[100005];

int main() {
    int n, k, r;
    scanf("%d %d %d", &n, &k, &r);
    for (int i = 0; i < k; ++i) {
        int nr;
        scanf("%d", &nr);
        tab[nr] = true;
    }
    int it = r;
    int kamery = 0;
    for (int i = 1; i <= it; ++i)
        kamery += tab[i];

    int postawione = 0;

    while (kamery < 2) {
        if (!tab[it])
            tab[it] = true;
        else
            tab[it - 1] = true;
        kamery++;
        postawione++;
    }

    while (it < n) {
        kamery += tab[++it];
        kamery -= tab[it - r];
        while (kamery < 2) {
            if (!tab[it])
                tab[it] = true;
            else
                tab[it - 1] = true;
            kamery++;
            postawione++;
        }
    }

    printf("%d", postawione);
    return 0;
}
