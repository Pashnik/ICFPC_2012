#ifndef ICFPC_2012_PATHFINDER_H
#define ICFPC_2012_PATHFINDER_H

#include "solver.h"

int equalCoordinates(Cell *start, Lambda *end);

Cell *getNeighbours(Cell *cell);

int canMove(struct cell **map, Cell *cell);

double heuristic(Cell *start, Lambda *end);

int findShortestPath(Robot *robot, Lambda *lambda,
                     Cell **map, const int *height, const int *width);

void printWay(const int *path, const unsigned int *hopes, const int *height, const int *width, Cell **map);

void printRobotsCommand(Cell *prev, Cell *current);

void rollBackIds(const int *height, const int *width, Cell **map);

Cell getCellById(const int *height, const int *width, Cell **map, int id);

#endif //ICFPC_2012_PATHFINDER_H
