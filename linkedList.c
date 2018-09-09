#include <stdlib.h>
#include "headers/linkedList.h"

void push(Node **head, struct lambda data) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->lambda = data;
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


struct lambda deleteNth(Node **head, int n) {
    if (n == 0) return pop(head);
    Node *prev = getNth(*head, n - 1);
    Node *elm = prev->next;
    struct lambda value = elm->lambda;
    prev->next = elm->next;
    free(elm);
    return value;
}

struct lambda pop(Node **head) {
    Node *prev = NULL;
    struct lambda value;
    if (head == NULL) exit(-1);
    prev = (*head);
    value = prev->lambda;
    (*head) = (*head)->next;
    free(prev);
    return value;
}
