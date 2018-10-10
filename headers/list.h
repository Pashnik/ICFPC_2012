#ifndef ICFPC_2012_LINKEDLIST_H
#define ICFPC_2012_LINKEDLIST_H

#include "cell.h"

typedef struct Node {
    Cell *cell;
    struct Node *next;
} Node;

Cell pop(Node **head);

int getIndex(Node *node, Cell *cell);

void deleteList(Node **head);

Cell deleteNth(Node **head, int n);

Node *getNth(Node *head, int n);

void push(Node **head, Cell *data);

int getMin(const double *f, Node *node);

int haveElement(Node *head, Cell *cell);

int getSize(Node *node);

#endif //ICFPC_2012_LINKEDLIST_H
