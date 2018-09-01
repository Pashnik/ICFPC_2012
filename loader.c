#include <memory.h>
#include "stdio.h"
#include "stdlib.h"
#include "loader.h"
#include "cell.h"

#define START_WIDTH 60
#define START_HEIGHT 10


void loadMap(char *fileName) {
    unsigned int isAdditionalRule = 0, heightPointer = 0;
    unsigned int currentHeight = START_HEIGHT;
    size_t widthPointer = 0;
    FILE *file;
    char *strPointer;
    char **array;
    file = fopen(fileName, "r");
    if (file == NULL) perror("Error in opening file");
    array = (char **) malloc(START_HEIGHT * sizeof(char *));
    while (1) {
        strPointer = (char *) malloc(START_WIDTH * sizeof(char *));
        strPointer = fgets(strPointer, START_WIDTH, file);
        if (!strPointer) break;
        if (heightPointer > currentHeight) {
            currentHeight += START_HEIGHT;
            array = (char **) realloc(array, currentHeight);
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

void setCells(char **array, const unsigned int *height, const size_t *width) {
    struct cell map[*height][*width];
    unsigned int y = *height;
    for (int i = 0; i < *height; ++i) {
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
                    break;
            }
            ++x;
        }
        --y;
    }
}

size_t getWidth(char **array, const unsigned int *height) {
    size_t maxWidth = 0;
    for (int i = 0; i < *height; ++i) {
        size_t currentWidth = strlen(array[i]);
        if (currentWidth > maxWidth) maxWidth = currentWidth;
    }
    return maxWidth;
}