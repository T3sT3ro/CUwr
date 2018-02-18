//
// Created by Tooster on 12.02.2018.
//

#include <cstdio>

const int N = 2 << 18;
const int P = 70;

int DP[P][N + 1];
int tab[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &tab[i]);

    int ret = 0;
    for (int p = 0; p < P; ++p) {
        for (int j = 0; j < n; ++j) {
            if (tab[j] == p) {
                ret = p > ret ? p : ret;
                DP[p][j] = j + 1;
            }
            else {
                if(p == 0 || DP[p-1][j] == -1 || DP[p-1][DP[p-1][j]] == -1)
                    DP[p][j] = -1;
                else{
                    ret = p > ret ? p : ret;
                    DP[p][j] = DP[p-1][DP[p-1][j]];
                }
            }
        }
        DP[p][n] = -1;
    }

    printf("%d", ret);
    return 0;
}