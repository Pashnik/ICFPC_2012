#ifndef ICFPC_2012_LINKEDLIST_H
#define ICFPC_2012_LINKEDLIST_H

#include "lambda.h"

typedef struct Node {
    struct lambda lambda;
    struct Node *next;
} Node;

struct lambda pop(Node **head);

struct lambda deleteNth(Node **head, int n);

Node *getNth(Node *head, int n);

void push(Node **head, struct lambda data);

#endif //ICFPC_2012_LINKEDLIST_H
