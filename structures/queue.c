#include <stdio.h>
#include "stdlib.h"
#include "../headers/queue.h"

void enqueue(Node **node, Cell *element) {
    pushToEnd(node, element);
}

Cell dequeue(Node **node) {
    return pop(node);
}

void pushToEnd(Node **node, Cell *element) {
    if ((*node) == NULL) push(node, element);
    else {
        Node *tmp = (Node *) malloc(sizeof(Node));
        tmp->cell = element;
        tmp->next = NULL;
        Node *nodeLast = getNth(*node, getSize(*node) - 1);
        nodeLast->next = tmp;
    }
}

