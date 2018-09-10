#include <stdlib.h>
#include <math.h>
#include "headers/finder.h"
#include "stdio.h"

#define NUM_OF_NEIGHBOURS 4
#define HOPES 100

/*
 * This method finds the shortest path from point a to point b, using the algorithm A-STAR
 */

int findShortestPath(Robot *robot, Lambda *lambda,
                     Cell **map, const int *height, const int *width) {
    int *path = malloc(HOPES * sizeof(int));
    unsigned int hopeNumber = 0, id = 2;
    Cell currentCell;
    currentCell.x = robot->x, currentCell.y = robot->y;
    map[currentCell.y][currentCell.x].id = 1;
    while (!equalCoordinates(&currentCell, lambda)) {
        int index = 0;
        double currentHeuristic = 0, minHeuristic = HOPES;
        Cell *neighbours = getNeighbours(&currentCell);
        for (int i = 0; i < NUM_OF_NEIGHBOURS; ++i) {
            int x = neighbours[i].x, y = neighbours[i].y;
            if (canMove(map, &neighbours[i]) && map[y][x].id == 0) {
                currentHeuristic = heuristic(&neighbours[i], lambda);
                map[y][x].id = id;
                if (currentHeuristic < minHeuristic) {
                    minHeuristic = currentHeuristic;
                    index = i;
                }
                ++id;
            }
        }
        path[hopeNumber] = map[currentCell.y][currentCell.x].id;
        currentCell.x = neighbours[index].x, currentCell.y = neighbours[index].y;
        ++hopeNumber;
    }
    robot->x = currentCell.x, robot->y = currentCell.y;
    path[hopeNumber] = map[currentCell.y][currentCell.x].id;
    printWay(path, &hopeNumber, height, width, map);

    rollBackIds(height, width, map);
    free(path);
    return 1;
}

Cell *getNeighbours(Cell *cell) {
    Cell *neighbours = (Cell *) malloc(NUM_OF_NEIGHBOURS * sizeof(Cell));
    neighbours[0].x = cell->x + 1, neighbours[0].y = cell->y;
    neighbours[1].x = cell->x - 1, neighbours[1].y = cell->y;
    neighbours[2].x = cell->x, neighbours[2].y = cell->y + 1;
    neighbours[3].x = cell->x, neighbours[3].y = cell->y - 1;
    return neighbours;
}

int equalCoordinates(Cell *start, Lambda *end) {
    if (start->x == end->x && start->y == end->y) return 1;
    return 0;
}

double heuristic(Cell *start, Lambda *end) {
    return sqrt(pow(start->x - end->x, 2) + pow(start->y - end->y, 2));
}

int canMove(Cell **map, Cell *cell) {
    int x = cell->x, y = cell->y;
    if (map[y][x].type == GROUND || map[y][x].type == LAMBDA || map[y][x].type == ROBOT) return 1;
    return 0;
}

void printWay(const int *path, const unsigned int *hopes, const int *height, const int *width, Cell **map) {
    Cell *prev = (Cell *) malloc(sizeof(Cell));
    Cell *current = (Cell *) malloc(sizeof(Cell));
    for (int i = 1; i <= *hopes; ++i) {
        int currentId = path[i], prevId = path[i - 1];
        for (int j = 0; j < *height; ++j) {
            for (int k = 0; k < *width; ++k) {
                if (map[j][k].id == currentId) {
                    *current = map[j][k];
                }
                if (map[j][k].id == prevId) {
                    *prev = map[j][k];
                }
            }
        }
        printRobotsCommand(prev, current);
    }
}

void printRobotsCommand(Cell *prev, Cell *current) {
    if (prev->y < current->y)
        printf("D");
    else {
        if (prev->y > current->y)
            printf("U");
    }
    if (prev->x < current->x)
        printf("R");
    else {
        if (prev->x > current->x)
            printf("L");
    }
    printf("\n");
}

void rollBackIds(const int *height, const int *width, Cell **map) {
    for (int i = 0; i < *height; ++i) {
        for (int j = 0; j < *width; ++j) {
            map[i][j].id = 0;
        }
    }
}