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

int getIndex(Node *head, Node *current) {
    int counter = 0;
    while (head) {
        if (current == head) return counter;
        head = head->next;
    }
    return -1;
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
    Element *value;
    if (head == NULL) exit(-1);
    prev = (*head);
    value = prev->element;
    (*head) = (*head)->next;
    free(prev);
    return *value;
}
