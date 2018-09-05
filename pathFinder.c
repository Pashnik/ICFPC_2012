#include <stdlib.h>
#include "headers/intellect.h"
#include "headers/cell.h"

/*
 * This file finds the shortest path from point a to point b, using the algorithm A-STAR
 */

void findShortestPath(struct robot robot, struct lambda lambda, struct cell **map) {
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