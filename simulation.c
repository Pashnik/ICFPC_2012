#include "headers/simulation.h"
#include "stdio.h"
#include "stdlib.h"
#include "headers/finder.h"

int score;

void reestablishPath(Node *returnPath, Cell **map, Node **lambdas, Cell *currentLambda) {
    int counter = 0;
    Cell *current;
    Cell *prev;
    Node *path = NULL;
    int listSize = getSize(returnPath);
    current = getNth(returnPath, 0)->cell;
    while (current->id != 0) {
        Cell *cur = (Cell *) malloc(sizeof(Cell));
        *cur = *current;
        push(&path, cur);
        prev = getNth(returnPath, listSize - current->id)->cell;
        selectCommand(current, prev);
        *current = *prev;
        ++counter;
    }
    map[current->y][current->x].type = EMPTY;
    checkPath(path, map, currentLambda, lambdas);
    deleteList(&returnPath);
}

void selectCommand(Cell *first, Cell *second) {
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

void getScore() {
    printf("Total score: %d\n", score);
}

void checkPath(Node *path, Cell **map, Cell *lambda, Node **lambdas) {
    Cell *current = getNth(path, 0)->cell;
    int counter = 0;
    while (path != NULL) {
        if (current->type == LAMBDA && counter != 0) {
            int index = getIndex(*lambdas, current);
            deleteLambda(lambdas, index);
            score += 25;
        }
        Cell *nextCell = getNth(path, 0)->cell;
        if (canMakeStep(map, nextCell)) { // доп проверка на лямбду
            map[current->y][current->x].type = EMPTY;
            *current = pop(&path);
            makeStep(map, current);
            simulate(map);
        } else {
            if (map[nextCell->y][nextCell->x].type != STONE) {
                map[nextCell->y][nextCell->x].type = STONE;
            }
            deleteList(&path);
            freeStack();
            findLocalPath(current, lambda, map, lambdas);
        }
        ++counter;
    }
    if (current->type == LAMBDA) {
        score += 25;
    }
}

void freeStack() {
    while (!isEmpty()) {
        popCommand();
    }
}

void makeStep(Cell **map, Cell *current) {
    --score;
    map[current->y][current->x].type = ROBOT;
    printf("%c\n", popCommand());
}

void simulate(Cell **map) {
    for (int i = mapHeight - 1; i >= 0; --i) {
        for (int j = mapWidth - 1; j >= 0; --j) {
            if (map[i][j].type == STONE) {
                if (map[i + 1][j].type == EMPTY) {
                    map[i + 1][j].type = STONE;
                    map[i][j].type = EMPTY;
                } else {
                    if (map[i + 1][j].type == STONE && map[i][j + 1].type == EMPTY
                        && map[i + 1][j + 1].type == EMPTY) {
                        map[i + 1][j + 1].type = STONE;
                        map[i][j].type = EMPTY;
                    } else {
                        if (map[i + 1][j].type == STONE && map[i][j - 1].type == EMPTY
                            && map[i + 1][j - 1].type == EMPTY) {
                            map[i + 1][j - 1].type = STONE;
                            map[i][j].type = EMPTY;
                        } else {
                            if (map[i + 1][j].type == LAMBDA && map[i][j + 1].type == EMPTY
                                && map[i + 1][j + 1].type == EMPTY) {
                                map[i + 1][j + 1].type = STONE;
                                map[i][j].type = EMPTY;
                            }
                        }
                    }
                }
            }
        }
    }
}

Cell **copyMap(Cell **map) {
    Cell **testMap = (Cell **) malloc(mapHeight * sizeof(Cell *));
    for (int i = 0; i < mapHeight; ++i) {
        testMap[i] = (Cell *) malloc(mapWidth * sizeof(Cell));
        for (int j = 0; j < mapWidth; ++j) {
            testMap[i][j].x = map[i][j].x, testMap[i][j].y = map[i][j].y;
            testMap[i][j].type = map[i][j].type;
        }
    }
    return testMap;
}

void freeMap(Cell **map) {
    for (int i = 0; i < mapHeight; ++i) {
        free(map[i]);
    }
    free(map);
}

int canMakeStep(Cell **map, Cell *cell) {
    Cell **testMap = copyMap(map);
    simulate(testMap);
    if (testMap[cell->y][cell->x].type != STONE) {
        freeMap(testMap);
        return 1;
    }
    freeMap(testMap);
    return 0;
}