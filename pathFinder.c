#include <stdlib.h>
#include <math.h>
#include "headers/intellect.h"
#include "headers/cell.h"
#include "headers/pathFinder.h"

/*
 * This file finds the shortest path from point a to point b, using the algorithm A-STAR
 */

void findShortestPath(struct robot robot, struct lambda lambda, struct cell **map) {
    struct cell currentCell;
    currentCell.x = robot.x, currentCell.y = robot.y;
    while (!equalCoordinates(currentCell, lambda)) {
        struct cell *neighbours = getNeighbours(currentCell);
        for (int i = 0; i < 4; ++i) {
            if (isPath(map, &currentCell)) {

            }
        }
    }
}

// It is possible to add not all neighbors at once, but exclude impassable cells
struct cell *getNeighbours(struct cell cell) {
    struct cell *neighbours = (struct cell *) malloc(4 * sizeof(struct cell));
    neighbours[0].x = cell.x + 1, neighbours[0].y = cell.y;
    neighbours[1].x = cell.x - 1, neighbours[1].y = cell.y;
    neighbours[2].x = cell.x, neighbours[2].y = cell.y + 1;
    neighbours[3].x = cell.x, neighbours[3].y = cell.y - 1;
    return neighbours;
}

unsigned int equalCoordinates(struct cell cell1, struct lambda cell2) {
    if (cell1.x != cell2.x || cell1.y != cell2.y) return 0;
    return 1;
}

double heuristic(struct cell cell1, struct cell cell2) {
    return sqrt(pow(cell1.x - cell2.x, 2) + pow(cell1.y - cell2.y, 2));
}

unsigned int isPath(struct cell **map, struct cell *cell) {
    // ??????????"!!!!!!!!!!!!!!
    return 0;
}