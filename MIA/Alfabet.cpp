//
// Created by Tooster on 06.11.2017.
//
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int tab[27][52];

int main() {
    ios_base::sync_with_stdio(false);
    string alfa = "abcdefghijklmnopqrstuvwxyz";
    string s;
    cin >> s;
    for (int i = 1; i <= 26; ++i) {
        for (int j = 1; j <= s.length(); ++j) {
            tab[i][j] = max(tab[i - 1][j], tab[i][j - 1]);
            if (alfa[i - 1] == s[j - 1])
                tab[i][j] = tab[i - 1][j - 1] + 1;
        }
    }

    cout << 26 - tab[26][s.length()];
    return 0;
}
