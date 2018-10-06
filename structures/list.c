#include <stdlib.h>
#include "../headers/list.h"

void push(Node **head, Cell *data) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->cell = data;
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

Cell deleteNth(Node **head, int n) {
    if (n == 0) return pop(head);
    Node *prev = getNth(*head, n - 1);
    Node *elm = prev->next;
    Cell *value = elm->cell;
    prev->next = elm->next;
    free(elm);
    return *value;
}

Cell pop(Node **head) {
    Node *prev = NULL;
    Cell *value = NULL;
    if (head == NULL) exit(-1);
    prev = (*head);
    value = prev->cell;
    (*head) = (*head)->next;
    free(prev);
    return *value;
}

int getMin(const double *f, Node *node) {
    double minValue = 100;
    int index = 0, counter = 0;
    while (node != NULL) {
        if (f[node->cell->id] < minValue) {
            minValue = f[node->cell->id];
            index = counter;
        }
        counter++;
        node = node->next;
    }
    return index;
}

int haveElement(Node *head, Cell *cell) {
    while (head != NULL) {
        if (head->cell->x == cell->x && head->cell->y == cell->y) return 1;
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

int getIndex(Node *node, Cell *cell) {
    int counter = 0;
    while (node != NULL) {
        if (node->cell->x == cell->x && node->cell->y == cell->y)
            return counter;
        ++counter;
        node = node->next;
    }
    return -1;
}
