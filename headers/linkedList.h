#ifndef ICFPC_2012_LINKEDLIST_H
#define ICFPC_2012_LINKEDLIST_H

#include "solver.h"

typedef struct Node {
    struct lambda value;
    struct Node *next;
} Node;

void pop(Node **head);

void deleteNth(Node **head, int n);

Node *getNth(Node *head, int n);

void push(Node **head, struct lambda data);

#endif //ICFPC_2012_LINKEDLIST_H
