#ifndef ICFPC_2012_QUEUE_H
#define ICFPC_2012_QUEUE_H

#include "linkedList.h"

void enqueue(Node **node, Element *element);

Element dequeue(Node **node);

void pushToEnd(Node **node, Element *element);

#endif //ICFPC_2012_QUEUE_H
