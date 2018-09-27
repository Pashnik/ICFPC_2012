#ifndef ICFPC_2012_LINKEDLIST_H
#define ICFPC_2012_LINKEDLIST_H

#include "element.h"

typedef struct Node {
    Element *element;
    struct Node *next;
} Node;

Element pop(Node **head);

Element deleteNth(Node **head, int n);

Node *getNth(Node *head, int n);

void push(Node **head, Element *data);

int getMin(const double *f, Node *node);

int haveElement(Node *head, Element *element);

int getSize(Node *node);

#endif //ICFPC_2012_LINKEDLIST_H
