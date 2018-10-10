#ifndef ICFPC_2012_PATHFINDER_H
#define ICFPC_2012_PATHFINDER_H

#include "solver.h"

int equalCoordinates(Cell *start, Cell *end);

Cell *getNeighbours(Cell *cell, Cell **map);

int canMove(Cell *cell);


int findLocalPath(Cell *robot, Cell *cellEnd,
                  Cell **map, Node **lambdas);

void makeWave(Cell **map, Cell *robot, Node **lambda);

double distance(Cell *start, Cell *end);

extern int mapHeight;

extern int mapWidth;

#endif //ICFPC_2012_PATHFINDER_H

