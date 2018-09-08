#include <stdlib.h>
#include "headers/linkedList.h"

void push(Node **head, struct lambda data) {
    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->value = data;
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


void deleteNth(Node **head, int n) {
    if (n == 0) {
        pop(head);
    } else {
        Node *prev = getNth(*head, n - 1);
        Node *elm = prev->next;
        prev->next = elm->next;
        free(elm);
    }
}

void pop(Node **head) {
    Node *prev = NULL;
    if (head == NULL) exit(-1);
    prev = (*head);
    (*head) = (*head)->next;
    free(prev);
}
