//
// Created by i300791 on 13.12.17.
//

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define DELIMETER "\n\t\r "
#define SIZE 6688
int dbg = 0;

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
    
    char newFileName[60] = "";
    strcat(newFileName, argc[1]);
    strcat(newFileName, "_filtered");
    FILE *outputFile = fopen(newFileName, "w");
   
    if (outputFile == NULL) {
        printf("Nie udalo sie utworzyc pliku wyjscia '%s'", newFileName);
        return EXIT_FAILURE;
    }
    // czytanie plików

  
    char *word1 = malloc(sizeof(char) * SIZE);
    char *word2 = malloc(sizeof(char) * SIZE);
    char *line = malloc(sizeof(char) * SIZE);
    int currentSize = SIZE;
 
    while (fgets(line, SIZE, inputFile) != NULL) {	
	while (strlen(line) > 0 && line[strlen(line) - 1] != '\n') {
            currentSize *= 2;
            line = realloc(line, sizeof(char) * currentSize);
            word1 = realloc(word1, sizeof(char) * currentSize);
            word2 = realloc(word2, sizeof(char) * currentSize);
            fgets(line + strlen(line), currentSize / 2, inputFile);
        }
        word2 = strtok(line, DELIMETER);
        while (word2 != NULL) {
            if (strcmp(word1, word2) != 0) {
                fprintf(outputFile, "%s%lu ", word2, strlen(word2));
                strcpy(word1, word2);
            }
            word2 = strtok(NULL, DELIMETER);
        }
        fprintf(outputFile, "\n");
    }
   
    fclose(outputFile);
    fclose(inputFile);
    return EXIT_SUCCESS;
}
