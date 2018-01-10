//
// Created by Tooster on 09.01.2018.
//

#include <stdio.h>
#include <stdbool.h>

#define isConst(c) ((c)=='0' || (c)=='1')
#define isVar(c) ('a' <= (c) && (c) <= 'z')

#define fromMask(i) (l & (1 << (i))) >> (i)

int priority(char c) {
    if (c == '=') return 0;
    if (c == '>') return 1;
    if (c == '|') return 2;
    if (c == '&') return 3;
    if (c == '~') return 4;
    return -1;
}

bool cmp(char a, char b) {
    return priority(a) <= priority(b);
}


int calc(char *str) {
    char zmienne[26];
    char onp[1010];
    int heap[1010];
    bool zmienne_var[26];
    for (int i = 0; i < 26; ++i)
        zmienne[i] = zmienne_var[i] = 0;
    for (int k = 0; k < 1010; ++k)
        heap[k] = onp[k] = '+';

    // map vars
    int it = 0;
    int zmienne_it = 0;
    int onp_it = 0;
    int heap_it = 0;
    // to ONP
    it = 0;
    while (str[it] != ';') {
        char x = str[it];
        if (isVar(x) || isConst(x)) {
            if (isVar(x)) {
                for (int i = 0; i < zmienne_it; ++i)
                    if (zmienne[i] == x) goto nope;
                zmienne[zmienne_it++] = x;
                nope:;
            }
            onp[onp_it++] = x;
        } else if (x == '(') {
            heap[heap_it++] = x;
        } else if (x == ')') {
            while (heap[heap_it - 1] != '(') {
                onp[onp_it++] = heap[--heap_it];
            }
            --heap_it; // opening (
        } else {
            if (x != '~')
                while (heap_it > 0) {
                    if (cmp(x, heap[heap_it - 1])) {
                        if (x == '>' && heap[heap_it - 1] == '>') break;
                        onp[onp_it++] = heap[--heap_it];
                    } else break;
                }
            heap[heap_it++] = x;
        }
        it++;
    }
    // append rest of heap
    while (heap_it > 0)
        onp[onp_it++] = heap[--heap_it];

    ///for (int j = 0; j < onp_it; ++j) printf("%c", onp[j]);
    printf("\n");

    int ile = 0;

    for (int l = 0; l < 1 << zmienne_it; ++l) {
        for (int i = 0; i < zmienne_it; ++i)
            zmienne_var[zmienne[i] - 'a'] = fromMask(i);

        heap_it = 0;
        for (int j = 0; j < onp_it; ++j) {
            char x = onp[j];
            if (isVar(x)) {
                heap[heap_it++] = zmienne_var[x - 'a'];
            } else if (isConst(x)) {
                heap[heap_it++] = x - '0';
            } else {
                if (x == '~')
                    heap[heap_it - 1] = !heap[heap_it - 1];
                else {
                    if (x == '=')
                        heap[heap_it - 2] = !(heap[heap_it - 1] ^ heap[heap_it - 2]);
                    else if (x == '>')
                        heap[heap_it - 2] = heap[heap_it - 1] | (!heap[heap_it - 2]);
                    else if (x == '|')
                        heap[heap_it - 2] = heap[heap_it - 1] | heap[heap_it - 2];
                    else if (x == '&')
                        heap[heap_it - 2] = heap[heap_it - 1] & heap[heap_it - 2];
                    heap_it--;
                }

            }
        }

        ile += heap[heap_it - 1];
    }

    return ile;
}

int main() {

    int n;
    int len = 1010;
    char buffer[len];
    for (int i = 0; i < len; ++i)
        buffer[i] = 0;
    scanf("%d ", &n);
    while (n--) {
        fgets(buffer, len, stdin);
        printf("%d\n", calc(buffer));
    }

    return 0;
}
