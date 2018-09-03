#include <memory.h>
#include "stdio.h"
#include "stdlib.h"
#include "headers/loader.h"
#include "headers/cell.h"

#define START_WIDTH 60
#define START_HEIGHT 60


void load(char *fileName) {
    unsigned int isAdditionalRule = 0, heightPointer = 0, widthPointer = 0;
    unsigned int currentHeight = START_HEIGHT;
    FILE *file;
    char *strPointer;
    char **array;
    file = fopen(fileName, "r");
    if (file == NULL) perror("Error in opening file");
    array = (char **) malloc(START_HEIGHT * sizeof(char *));
    while (1) {
        strPointer = (char *) malloc(START_WIDTH * sizeof(char));
        strPointer = fgets(strPointer, START_WIDTH, file);
        if (!strPointer) break;
        if (heightPointer > currentHeight) {
            currentHeight += START_HEIGHT;
            *array = (char *) realloc(*array, currentHeight * sizeof(char));
        }
        if (*strPointer == '\n') isAdditionalRule = 1;
        if (!isAdditionalRule) {
            array[heightPointer] = strPointer;
            ++heightPointer;
        } else {
            /*
             * submission of rule changes
             */
        }
    }
    widthPointer = getWidth(array, &heightPointer);
    setCells(array, &heightPointer, &widthPointer);
}

void setCells(char **array, const unsigned int *height, const unsigned int *width) {
    struct cell **map = (struct cell **) malloc(*height * sizeof(struct cell *));
    unsigned int y = *height;
    for (int i = 0; i < *height; ++i) {
        map[i] = (struct cell *) malloc(*width * sizeof(struct cell));
        unsigned int x = 1;
        for (int j = 0; j < *width - 1; ++j) {
            map[i][j].x = x, map[i][j].y = y;
            char symbol = array[i][j];
            switch (symbol) {
                case 'R':
                    map[i][j].type = ROBOT;
                    break;
                case '*':
                    map[i][j].type = STONE;
                    break;
                case 'L':
                    map[i][j].type = CLOSED_OUT;
                    break;
                case '.':
                    map[i][j].type = GROUND;
                    break;
                case '#':
                    map[i][j].type = WALL;
                    break;
                case '\\':
                    map[i][j].type = LAMBDA;
                    break;
                case 'O':
                    map[i][j].type = OPENED_OUT;
                    break;
                case ' ':
                    map[i][j].type = EMPTY;
                    map[i][j].x = 0, map[i][j].y = 0;
                    break;
                default:
                    map[i][j].type = EMPTY;
                    map[i][j].x = 0, map[i][j].y = 0;
                    break;
            }
            ++x;
        }
        --y;
    }
}

unsigned int getWidth(char **array, const unsigned int *height) {
    size_t maxWidth = 0;
    for (int i = 0; i < *height; ++i) {
        size_t currentWidth = strlen(array[i]);
        if (currentWidth > maxWidth) maxWidth = currentWidth;
    }
    return (unsigned int) maxWidth;
}
