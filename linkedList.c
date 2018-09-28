#include <stdlib.h>
#include "headers/linkedList.h"

void push(Node **head, Element *data) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->element = data;
    tmp->next = (*head);
    (*head) = tmp;
}


Node *getNth(Node *head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

Element deleteNth(Node **head, int n) {
    if (n == 0) return pop(head);
    Node *prev = getNth(*head, n - 1);
    Node *elm = prev->next;
    Element *value = elm->element;
    prev->next = elm->next;
    free(elm);
    return *value;
}

Element pop(Node **head) {
    Node *prev = NULL;
    Element *value = NULL;
    if (head == NULL) exit(-1);
    prev = (*head);
    value = prev->element;
    (*head) = (*head)->next;
    free(prev);
    return *value;
}

int getMin(const double *f, Node *node) {
    double minValue = 100;
    int index = 0, counter = 0;
    while (node != NULL) {
        if (f[node->element->id] < minValue) {
            minValue = f[node->element->id];
            index = counter;
        }
        counter++;
        node = node->next;
    }
    return index;
}

int haveElement(Node *head, Element *element) {
    while (head != NULL) {
        if (head->element->x == element->x && head->element->y == element->y) return 1;
        head = head->next;
    }
    return 0;
}


int getSize(Node *node) {
    int counter = 0;
    while (node != NULL) {
        ++counter;
        node = node->next;
    }
    return counter;
}
