#include <stdlib.h>
#include <math.h>
#include "headers/localFinder.h"
#include "stdio.h"

#define NUM_OF_NEIGHBOURS 4

/*
 * This method finds the shortest local path from point a to point b, using the algorithm A-STAR
 */

int findShortestPath(Element *robot, Element *lambda,
                     Cell **map, const int *height, const int *width) {
    Node *closed = NULL; // items we've already reviewed
    Node *opened;
    push(&opened, robot); //items required for viewing
    Node *path = NULL;
    int *g = (int *) malloc(100 * (sizeof(int)));
    double *f = (double *) malloc(100 * sizeof(double));
    g[0] = 0;
    f[0] = heuristic(robot, lambda, &g[0]);
    while (opened != NULL) {
        Node *current = getMin(opened, f);
        if (equalCoordinates(current->element, lambda)) return 1;

    }
    return 1;
}

Element *getNeighbours(Element *element) {
    Element *neighbours = (Element *) malloc(NUM_OF_NEIGHBOURS * sizeof(Element));
    neighbours[0].x = element->x + 1, neighbours[0].y = element->y;
    neighbours[1].x = element->x - 1, neighbours[1].y = element->y;
    neighbours[2].x = element->x, neighbours[2].y = element->y + 1;
    neighbours[3].x = element->x, neighbours[3].y = element->y - 1;
    return neighbours;
}

int equalCoordinates(Element *start, Element *end) {
    if (start->x == end->x && start->y == end->y) return 1;
    return 0;
}

double heuristic(Element *start, Element *end, int *hopeNumber) {
    return sqrt(pow(start->x - end->x, 2) + pow(start->y - end->y, 2)) + *hopeNumber;
}

int canMove(Cell **map, Element *cell) {
    int x = cell->x, y = cell->y;
    if (map[y][x].type == GROUND || map[y][x].type == LAMBDA || map[y][x].type == ROBOT ||
        map[y][x].type == EMPTY)
        return 1;
    return 0;
}

void printWay(const int *path, const unsigned int *hopes, const int *height, const int *width, Cell **map) {
    /* Cell *prev = (Cell *) malloc(sizeof(Cell));
     Cell *current = (Cell *) malloc(sizeof(Cell));
     *prev = getCellById(height, width, map, path[0]);
     for (int i = 1; i <= *hopes; ++i) {
         *current = getCellById(height, width, map, path[i]);
         printRobotsCommand(prev, current);
         *prev = *current;
     }
     */
}

void printRobotsCommand(Element *prev, Element *current) {
    if (prev->y < current->y) printf("D");
    else {
        if (prev->y > current->y) printf("U");
        else {
            if (prev->x < current->x) printf("R");
            else {
                if (prev->x > current->x) printf("L");
            }
        }
    }
    printf("\n");
}

Node *getMin(Node *node, const double *f) {
    Node *minNode = (Node *) malloc(sizeof(Node));
    double minValue = 100;
    Node *head = node;
    while (node != NULL) {
        if (f[getIndex(head, node)] < minValue) {
            minValue = f[getIndex(head, node)];
            minNode = node;
        }
        node = node->next;
    }
    return minNode;
}