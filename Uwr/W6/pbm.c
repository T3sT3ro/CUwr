//
// Created by Tooster on 20.11.2017.
//

#include <stdio.h>
#include <ctype.h>

int obraz[1000][1000];

void DFS(int i, int j) {
    obraz[i][j] = 0;
    if (obraz[i - 1][j] == 1)
        DFS(i - 1, j);
    if (obraz[i - 1][j - 1] == 1)
        DFS(i - 1, j - 1);
    if (obraz[i][j - 1] == 1)
        DFS(i, j - 1);
    if (obraz[i + 1][j - 1] == 1)
        DFS(i + 1, j - 1);
    if (obraz[i + 1][j] == 1)
        DFS(i + 1, j);
    if (obraz[i + 1][j + 1] == 1)
        DFS(i + 1, j + 1);
    if (obraz[i][j + 1] == 1)
        DFS(i, j + 1);
    if (obraz[i - 1][j + 1] == 1)
        DFS(i - 1, j + 1);
}

int main() {
    int w = 0, h = 0;

    int FLAG = 1;
    int row = 1;
    int col = 1;
    char character = getchar();
    while (character != EOF) {
        if (character == '#') // comments
            FLAG *= -1;
        else if (FLAG < 0 && character == '\n') // end of comments
            FLAG *= 1000;
        else if (FLAG == 1 && character == 'P') // magic number
            FLAG++;
        else if (FLAG == 2 && character == '1') // magic number
            FLAG++;
        else if (FLAG == 3 && isspace(character)) // whitespace
            FLAG++;
        else if (FLAG == 4 && isdigit(character)) { // width
            w *= 10;
            w += character - '0';
        } else if (FLAG == 4 && isspace(character)) // whitespace
            FLAG++;
        else if (FLAG == 5 && isdigit(character)) { // height
            h *= 10;
            h += character - '0';
        } else if (FLAG == 5 && isspace(character)) // whitespace
            FLAG++;
        else if (FLAG == 6 && isdigit(character)) { // reading bits skipping whitespaces
            if (col == w + 1) {
                row++;
                col = 1;
            }
            obraz[row][col++] = character - '0';
        }
        if (FLAG > -1000)
            character = getchar();
        else
            FLAG /= -1000;
    }

//    for (int i = 0; i <= h+1; i++) {
//        for (int j = 0; j <= w+1; ++j)
//            printf("%d", obraz[i][j]);
//        printf("\n");
//    }

    int obszary = 0;
    for (int i = 1; i <= h; i++)
        for (int j = 1; j <= w; ++j)
            if (obraz[i][j] == 1) {
                DFS(i, j);
                obszary++;
            }

    printf("%d\n", obszary);
    return 0;
}