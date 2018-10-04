#include <stdio.h>
#include "stdlib.h"
#include "headers/queue.h"

void enqueue(Node **node, Element *element) {
    pushToEnd(node, element);
}

Element dequeue(Node **node) {
    return pop(node);
}

void pushToEnd(Node **node, Element *element) {
    if ((*node) == NULL) push(node, element);
    else {
        Node *tmp = (Node *) malloc(sizeof(Node));
        tmp->element = element;
        tmp->next = NULL;
        Node *nodeLast = getNth(*node, getSize(*node) - 1);
        nodeLast->next = tmp;
    }
}

