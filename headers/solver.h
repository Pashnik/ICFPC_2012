#ifndef ICFPC_2012_INTELLECT_H
#define ICFPC_2012_INTELLECT_H

#include "linkedList.h"

void start(struct cell **map, const int *height, const int *width);

struct robot {
    int x;
    int y;
} robot;

struct wall {
    int x;
    int y;
};

struct exit {
    int x;
    int y;
} out;

void setInitialInf(struct cell **map, const int *height, const int *width,
                   Node **node, struct robot *robot, struct wall *walls, struct exit *out);

int findNextLambda(Node *node, struct robot *robot);

struct cell getLambdaById(int id, struct cell **map, const int *height, const int *width);

#endif //ICFPC_2012_INTELLECT_H
