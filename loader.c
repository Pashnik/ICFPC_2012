#include "stdio.h"
#include "stdlib.h"

#define START_WIDTH 60
#define START_HEIGHT 10

char **map;

void loadMap(char *fileName) {
    unsigned int isAdditionalRule = 0, heightPointer = 0;
    unsigned int currentHeight = START_HEIGHT;
    FILE *file;
    char *strPointer;
    file = fopen(fileName, "r");
    if (file == NULL) perror("Error in opening file");
    map = (char **) malloc(START_HEIGHT * sizeof(char *));
    while (1) {
        strPointer = (char *) malloc(START_WIDTH * sizeof(char));
        strPointer = fgets(strPointer, START_WIDTH, file);
        if (!strPointer) break;
        if (heightPointer > currentHeight) {
            currentHeight += START_HEIGHT;
            map = (char **) realloc(map, currentHeight);
        }
        if (*strPointer == '\n') isAdditionalRule = 1;
        if (!isAdditionalRule) map[heightPointer] = strPointer;
        else {
            /*
             * submission of rule changes
             */
        }
        ++heightPointer;
    }
}

