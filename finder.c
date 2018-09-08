#include <stdlib.h>
#include <math.h>
#include "headers/solver.h"
#include "headers/cell.h"
#include "headers/finder.h"

#define NUM_OF_NEIGHBOURS 4
#define HOPES 100

/*
 * This method finds the shortest path from point a to point b, using the algorithm A-STAR
 */

int *findShortestPath(struct robot *robot, struct lambda *lambda, struct cell **map) {
    int *path = malloc(HOPES * sizeof(int));
    unsigned int hopeNumber = 0, id = 2;
    struct cell currentCell;
    currentCell.x = (*robot).x, currentCell.y = (*robot).y;
    while (!equalCoordinates(&currentCell, lambda)) {
        int index = 0;
        double currentHeuristic = 0, minHeuristic = HOPES;
        struct cell *neighbours = getNeighbours(&currentCell);
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
    (*robot).x = currentCell.x, (*robot).y = currentCell.y;
    return path;
}

struct cell *getNeighbours(struct cell *cell) {
    struct cell *neighbours = (struct cell *) malloc(NUM_OF_NEIGHBOURS * sizeof(struct cell));
    neighbours[0].x = (*cell).x + 1, neighbours[0].y = (*cell).y;
    neighbours[1].x = (*cell).x - 1, neighbours[1].y = (*cell).y;
    neighbours[2].x = (*cell).x, neighbours[2].y = (*cell).y + 1;
    neighbours[3].x = (*cell).x, neighbours[3].y = (*cell).y - 1;
    return neighbours;
}

int equalCoordinates(struct cell *start, struct lambda *end) {
    if ((*start).x == (*end).x && (*start).y == (*end).y) return 1;
    return 0;
}

double heuristic(struct cell *start, struct lambda *end) {
    return sqrt(pow((*start).x - (*end).x, 2) + pow((*start).y - (*end).y, 2));
}

int canMove(struct cell **map, struct cell *cell) {
    int x = (*cell).x, y = (*cell).y;
    if (map[y][x].type == GROUND || map[y][x].type == LAMBDA) return 1;
    return 0;
}