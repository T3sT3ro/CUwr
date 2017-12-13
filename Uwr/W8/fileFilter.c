//
// Created by i300791 on 13.12.17.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define DELIMETER "\n\t\r "
#define SIZE 1024

int main(int argv, char *argc[]) {
    // otwieranie plików
    if (argv <= 1) {
        printf("Nie podano nazwy pliku w argumentach wywolania programu.");
        return EXIT_FAILURE;
    }
    FILE *inputFile = fopen(argc[1], "r");
    if (inputFile == NULL) {
        printf("Nie udalo sie otworzyc pliku '%s'", argc[1]);
        return EXIT_FAILURE;
    }
    char *newFileName;
    strcat(newFileName, argc[1]);
    strcat(newFileName, "_filtered");
    FILE *outputFile = fopen(newFileName, "w");

    // czytanie plików

    char *word1;
    char *word2;
    char *line = malloc(sizeof(char) * SIZE);
    int currentSize = SIZE;

    while (line != NULL) {
        fgets(line, SIZE, inputFile);
        while (line[strlen(line)-1] != '\n') {
            currentSize *= 2;
            line = realloc(line, sizeof(char) * currentSize);
        }
        word2 = strtok(line, DELIMETER);
        while (word2 != NULL) {
            word2 = strtok(NULL, DELIMETER);
            if (strcmp(word1, word2) != 0) {
                fprintf(outputFile, word2);
                fprintf(outputFile, "%d", strlen(word2));
                strcpy(word1, word2);
            }
        }
    }

    fclose(outputFile);
    fclose(inputFile);
}