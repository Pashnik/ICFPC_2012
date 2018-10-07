#ifndef ICFPC_2012_SIMULATION_H
#define ICFPC_2012_SIMULATION_H

#include "solver.h"
#include "stack.h"

void printRobotsCommand(Cell *first, Cell *second);

void reestablishPath(Node *path, Cell **map, Node **lambdas);

void printScore();

#endif //ICFPC_2012_SIMULATION_H
