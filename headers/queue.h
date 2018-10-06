#ifndef ICFPC_2012_QUEUE_H
#define ICFPC_2012_QUEUE_H

#include "linkedList.h"

void enqueue(Node **node, Cell *element);

Cell dequeue(Node **node);

void pushToEnd(Node **node, Cell *element);

#endif //ICFPC_2012_QUEUE_H
