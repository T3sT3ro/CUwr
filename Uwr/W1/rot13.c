#include <stdio.h>
#include <stdbool.h>

#define nl printf("\n")

#define ALPHABET_LENGTH 26
#define ROT 13

// Maksymilian Polarczyk
// Lista 2
// zadanie - szyfr cezara


int rot3(){
    printf("#      Program do szyfru cezara (rot13)      #"); nl;
    printf("# Oddzielaj znaki spacjami, enter potwierdza #"); nl;

    char c;
    while((c=fgetc(stdin))!='\n'){\
        char c_rot = c;
        bool BIG = false, SMALL = false;
        if(c >= 'A' && c <= 'Z') BIG = true;
        if(c >= 'a' && c <= 'z') SMALL = true;
        if(BIG || SMALL) {
            int base = 'A';
            if (SMALL) base = 'a';
            c_rot -= base;
            c_rot += ROT;
            c_rot %= ALPHABET_LENGTH;
            c_rot += base;
        }
        printf("%c", c_rot);
    }
    nl;
    return 0;
}
