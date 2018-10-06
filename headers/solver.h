#ifndef ICFPC_2012_INTELLECT_H
#define ICFPC_2012_INTELLECT_H

#include "linkedList.h"
#include "cell.h"

void start(Cell **map);

void setInitialInf(Cell **map, Node **lambda, Cell *robot, Node **wall, Cell *exit);

int findNextLambda(Node *node, Cell *robot);

void makeWave(Cell **map, Cell *robot, Node **lambda);

#endif //ICFPC_2012_INTELLECT_H
