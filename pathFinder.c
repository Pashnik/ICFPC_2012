#include <stdlib.h>
#include <math.h>
#include "headers/intellect.h"
#include "headers/cell.h"
#include "headers/pathFinder.h"

#define NUM_OF_NEIGHBOURS 4

/*
 * This file finds the shortest path from point a to point b, using the algorithm A-STAR
 */

void findShortestPath(struct robot *robot, struct lambda *lambda, struct cell **map) {
    unsigned int *path = malloc(100 * sizeof(int));
    struct cell currentCell;
    currentCell.x = (*robot).x, currentCell.y = (*robot).y;
    while (equalCoordinates(currentCell, *lambda) != 0) {
        unsigned int id = 2, pathPointer = 0;
        int index = 0;
        double currentHeuristic = 0, minHeuristic = 100;
        struct cell *neighbours = getNeighbours(currentCell);
        for (int i = 0; i < NUM_OF_NEIGHBOURS; ++i) {
            if (isPath(map, &neighbours[i]) != 0) {
                currentHeuristic = heuristic(neighbours[i], *lambda);
                map[neighbours[i].y][neighbours[i].x].id = id;
                if (currentHeuristic < minHeuristic) {
                    minHeuristic = currentHeuristic;
                    index = i;
                }
                ++id;
            }
        }
        currentCell.x = neighbours[index].x, currentCell.y = neighbours[index].y;
        path[pathPointer] = neighbours[index].id;
        ++pathPointer;
    }
}

// It is possible to add not all neighbors at once, but exclude impassable cells
struct cell *getNeighbours(struct cell cell) {
    struct cell *neighbours = (struct cell *) malloc(NUM_OF_NEIGHBOURS * sizeof(struct cell));
    neighbours[0].x = cell.x + 1, neighbours[0].y = cell.y;
    neighbours[1].x = cell.x - 1, neighbours[1].y = cell.y;
    neighbours[2].x = cell.x, neighbours[2].y = cell.y + 1;
    neighbours[3].x = cell.x, neighbours[3].y = cell.y - 1;
    return neighbours;
}

unsigned int equalCoordinates(struct cell cell1, struct lambda cell2) {
    if (cell1.x != cell2.x || cell1.y != cell2.y) return 1;
    return 0;
}

double heuristic(struct cell cell1, struct lambda cell2) {
    int x1 = cell1.x;
    int x2 = cell2.x;
    int y1 = cell1.y;
    int y2 = cell2.y;
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

unsigned int isPath(struct cell **map, struct cell *cell) {
    unsigned int x = (*cell).x, y = (*cell).y;
    if (map[y][x].type != WALL && map[y][x].type != STONE && map[y][x].type != CLOSED_OUT) return 1;
    return 0;
}