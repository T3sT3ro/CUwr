//
// Created by Tooster on 23.10.2017.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const int BUFFER_SIZE = 6001;

enum COMPARE_FLAG {
    EMPTY,
    WHITESPACE,
    NORMAL
};

bool isSpace(char x) {
    return x == ' ' ||
           x == '\t' ||
           x == '\n' ||
           x == '\v' ||
           x == '\f' ||
           x == '\r' ||
           x == '\0';
}

enum COMPARE_FLAG checkLine(char *a) {
    if (a[0] == '\n' || a[0] == '\r' || a[0] == '\f') {
        return EMPTY;
    }
    for (int i = BUFFER_SIZE - 1; i >= 0; --i) {
        if (!isSpace(a[i])) {
            return NORMAL;
        }
    }
    return WHITESPACE;
}


bool compareEqual(char *a, char *b) {
    // when two flags are different, then lines are different
    if (checkLine(a) != checkLine(b))
        return false;
    // exception 1: if line b is NEWLINE return true
    if (checkLine(b) == EMPTY)
        return true;

    bool TRIM_FLAG = true;
    // exception 2: if lines have whitespaces, don't trim
    if (checkLine(a) == WHITESPACE && checkLine(b) == WHITESPACE)
        TRIM_FLAG = false;

    for (int i = BUFFER_SIZE - 1; i >= 0; --i) {
        if (TRIM_FLAG) {
            if (!isSpace(a[i]) || !isSpace(b[i]))
                TRIM_FLAG = false;
        }
        if (!TRIM_FLAG) {
            if (a[i] != b[i])
                return false;
        }
    }
    return true;
}

int main() {
    char bufferClear[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; ++i)
        bufferClear[i] = ' ';
    char buffer[BUFFER_SIZE];
    memcpy(&buffer, &bufferClear, sizeof buffer);
    char buffer2[BUFFER_SIZE];
    memcpy(&buffer2, &bufferClear, sizeof buffer2);


    // if empty
    if (!fgets(buffer, BUFFER_SIZE, stdin))
        return 0;
    fputs(buffer, stdout);

    while (fgets(buffer2, BUFFER_SIZE, stdin)) {
        if (compareEqual(buffer, buffer2)) {
            memcpy(&buffer, &buffer2, sizeof buffer);
        } else {
            memcpy(&buffer, &buffer2, sizeof buffer);
            fputs(buffer2, stdout);
        }
    }
    return 0;
}
