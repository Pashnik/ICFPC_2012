#ifndef ICFPC_2012_INTELLECT_H
#define ICFPC_2012_INTELLECT_H

#include "linkedList.h"
#include "cell.h"

void start(Cell **map, const int *height, const int *width);

typedef struct robot {
    int x;
    int y;
} Robot;

typedef struct wall {
    int x;
    int y;
} Wall;

typedef struct exit {
    int x;
    int y;
} Exit;

void setInitialInf(Cell **map, const int *height, const int *width,
                   Node **node, Robot *robot, Wall *walls, Exit *out);

int findNextLambda(Node *node, Robot *robot);

#endif //ICFPC_2012_INTELLECT_H
