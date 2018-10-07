#include "headers/simulation.h"
#include "stdio.h"
#include "stdlib.h"

int score;

void reestablishPath(Node *path, Cell **map, Node **lambdas) {
    int counter = 0;
    Cell *prev;
    Cell *current;
    int listSize = getSize(path);
    current = getNth(path, 0)->cell;
    while (current->id != 0) {
        if (map[current->y][current->x].type == LAMBDA) score += 25;
        if (current->type == LAMBDA && counter != 0) {
            int index = getIndex(*lambdas, current);
            deleteLambda(lambdas, index);
            score += 25;
        }
        map[current->y][current->x].type = EMPTY;
        prev = getNth(path, listSize - current->id)->cell;
        printRobotsCommand(current, prev);
        *current = *prev;
        ++counter;
    }
    while (!isEmpty()) {
        printf("%c\n", popCommand());
        --score;
    }
    free(path);
}

void printRobotsCommand(Cell *first, Cell *second) {
    if (first->y < second->y) pushCommand('U');
    else {
        if (first->y > second->y) pushCommand('D');
        else {
            if (first->x < second->x) pushCommand('L');
            else {
                if (first->x > second->x) pushCommand('R');
            }
        }
    }
}


void printScore() {
    printf("Total score: %d\n", score);
}