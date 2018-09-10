#include <memory.h>
#include "stdio.h"
#include "stdlib.h"
#include "headers/loader.h"
#include "headers/solver.h"

#define START_WIDTH 60
#define START_HEIGHT 60

void load(char *fileName) {
    int isAdditionalRule = 0, heightPointer = 0, widthPointer = 0;
    int currentHeight = START_HEIGHT;
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
    Cell **map = setCells(array, &heightPointer, &widthPointer);
    start(map, &heightPointer, &widthPointer);
}

Cell **setCells(char **array, const int *height, const int *width) {
    Cell **map = (Cell **) malloc(*height * sizeof(Cell *));
    for (int i = 0; i < *height; ++i) {
        map[i] = (Cell *) malloc(*width * sizeof(Cell));
        for (int j = 0; j < *width; ++j) {
            map[i][j].x = j, map[i][j].y = i;
            map[i][j].id = 0;
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
                default:
                    map[i][j].type = EMPTY;
                    map[i][j].x = 0, map[i][j].y = 0;
                    break;
            }
        }
    }
    return map;
}

int getWidth(char **array, const int *height) {
    size_t maxWidth = 0;
    for (int i = 0; i < *height; ++i) {
        size_t currentWidth = strlen(array[i]);
        if (currentWidth > maxWidth) maxWidth = currentWidth;
    }
    return (int) maxWidth - 1;
}
