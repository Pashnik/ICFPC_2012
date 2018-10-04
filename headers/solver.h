#ifndef ICFPC_2012_INTELLECT_H
#define ICFPC_2012_INTELLECT_H

#include "linkedList.h"
#include "cell.h"
#include "element.h"

void start(Cell **map, const int *height, const int *width);

void setInitialInf(Cell **map, const int *height, const int *width,
                   Node **lambda, Element *robot, Node **wall, Element *exit);

int findNextLambda(Node *node, Element *robot);

void makeWave(Cell **map, const int *height, const int *width, Element *robot);

#endif //ICFPC_2012_INTELLECT_H
