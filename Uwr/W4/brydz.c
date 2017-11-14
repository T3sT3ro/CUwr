//
// Created by Tooster on 13.11.2017.
//

#include <stdio.h>

#define toInt(mm, dd, hh, mins, sec) (((mm)<<22) | ((dd)<<17) | ((hh)<<12) | ((mins)<<6) | (sec));
#define monthB   0b11110000000000000000000000
#define dayB     0b00001111100000000000000000
#define hourB    0b00000000011111000000000000
#define minuteB  0b00000000000000111111000000
#define secondB  0b00000000000000000000111111
#define month(x)  (((x)&monthB)  >>22   )
#define day(x)    (((x)&dayB)    >>17   )
#define hour(x)   (((x)&hourB)   >>12   )
#define minute(x) (((x)&minuteB) >>6    )
#define second(x) (((x)&secondB)        )

#define min(a, b) (((a)<(b)) ? (a) : (b))
#define max(a, b) (((a)>(b)) ? (a) : (b))

int pocz[512];
int konc[512];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int mm, dd, hh, mins, sec;
        scanf("%d %d %d %d %d", &mm, &dd, &hh, &mins, &sec);
        pocz[i] = toInt(mm, dd, hh, mins, sec);
        scanf("%d %d %d %d %d", &mm, &dd, &hh, &mins, &sec);
        konc[i] = toInt(mm, dd, hh, mins, sec);
    }

    int czas = 0;   // czas grania
    int u, v, w, x;    // czterech brydzystow apokalipsy
    int poczBest = 0;
    int koncBest = 0;
    for (int i = 0; i < n; ++i) { // pierwszy
        int a1 = pocz[i];
        int b1 = konc[i];

        for (int j = i + 1; j < n; ++j) { // drugi
            int a2 = max(a1, pocz[j]);
            int b2 = min(b1, konc[j]);

            for (int k = j + 1; k < n; ++k) { // trzeci
                int a3 = max(a2, pocz[k]);
                int b3 = min(b2, konc[k]);

                for (int l = k + 1; l < n; ++l) { // czwarty
                    int a4 = max(a3, pocz[l]);
                    int b4 = min(b3, konc[l]);
                    if (czas < b4 - a4) {
                        u = i;
                        v = j;
                        w = k;
                        x = l;
                        czas = b4 - a4;
                        poczBest = a4;
                        koncBest = b4;
                    }
                }
            }
        }
    }
    if (czas == 0) {
        printf("NOT FOUND!");
        return 0;
    }
    printf("%d %d %d %d %d\n", czas, x, w, v, u);
    printf("%d: %d %d %d %d %d\n", poczBest, month(poczBest), day(poczBest), hour(poczBest), minute(poczBest),
           second(poczBest));
    printf("%d: %d %d %d %d %d\n", koncBest, month(koncBest), day(koncBest), hour(koncBest), minute(koncBest),
           second(koncBest));
    return 0;
}