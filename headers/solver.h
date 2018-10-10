#ifndef ICFPC_2012_INTELLECT_H
#define ICFPC_2012_INTELLECT_H

#include "list.h"
#include "cell.h"

void start(Cell **map);

void setInitialInf(Cell **map, Cell *robot, Node **wall, Cell *wayOut);

int findNextLambda(Node *node, Cell *robot);

Cell deleteLambda(Node **lambdas, int id);

int haveLambdas(Cell **map);

#endif //ICFPC_2012_INTELLECT_H
