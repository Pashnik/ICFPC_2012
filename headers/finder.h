#ifndef ICFPC_2012_PATHFINDER_H
#define ICFPC_2012_PATHFINDER_H

#include "cell.h"
#include "solver.h"

int equalCoordinates(struct cell *start, struct lambda *end);

struct cell *getNeighbours(struct cell *cell);

int canMove(struct cell **map, struct cell *cell);

double heuristic(struct cell *start, struct lambda *end);

int *findShortestPath(struct robot *robot, struct lambda *lambda, struct cell **map);

#endif //ICFPC_2012_PATHFINDER_H
