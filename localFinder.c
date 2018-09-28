#include <stdlib.h>
#include <math.h>
#include "headers/localFinder.h"
#include "headers/stack.h"
#include "stdio.h"

#define NUM_OF_NEIGHBOURS 4
#define SIZE 100

/*
 * This method finds the shortest local path from point a to point b, using the algorithm A-STAR
 */

int findShortestPath(Element *robot, Element *lambda, Cell **map) {
    Node *closed = NULL; // items we've already reviewed
    Node *opened = NULL; //items required for viewing
    Node *path = NULL;
    push(&opened, robot);
    robot->id = 0;
    int id = 1;
    double *g = (double *) malloc(SIZE * (sizeof(double)));
    double *f = (double *) malloc(SIZE * sizeof(double));
    g[0] = 0;
    f[0] = distance(robot, lambda);
    while (opened != NULL) {
        int minIndex = getMin(f, opened);
        Element *current = (Element *) malloc(sizeof(Element));
        *current = deleteNth(&opened, minIndex);
        if (equalCoordinates(current, lambda)) {
            push(&path, current);
            reestablishPath(path);
            return 1;
        }
        push(&closed, current);
        Element *neighbours = getNeighbours(current);
        for (int i = 0; i < NUM_OF_NEIGHBOURS; ++i) {
            if (!haveElement(closed, &neighbours[i]) && canMove(map, &neighbours[i])) {
                double temp = g[current->id] + distance(current, &neighbours[i]);
                if (!haveElement(opened, &neighbours[i]) || temp < g[neighbours[i].id]) {
                    neighbours[i].id = id;
                    push(&path, current);
                    g[neighbours[i].id] = temp;
                    f[neighbours[i].id] = g[neighbours[i].id] + distance(&neighbours[i], lambda);
                    ++id;
                }
                if (!haveElement(opened, &neighbours[i])) push(&opened, &neighbours[i]);
            }
        }
    }
    return 0;
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

double distance(Element *start, Element *end) {
    return sqrt(pow(start->x - end->x, 2) + pow(start->y - end->y, 2));
}

int canMove(Cell **map, Element *cell) {
    int x = cell->x, y = cell->y;
    if (map[y][x].type == GROUND || map[y][x].type == LAMBDA || map[y][x].type == ROBOT ||
        map[y][x].type == EMPTY)
        return 1;
    return 0;
}

void printRobotsCommand(Element *first, Element *second) {
    if (first->y < second->y) pushCommand('U');
    else {
        if (first->y > second->y) pushCommand('D');
        else {
            if (first->x < second->x) pushCommand('L');
            else {
                if (first->x > second->x) pushCommand('R');
            }
        }
    }
}

void reestablishPath(Node *path) {
    Element *prev;
    Element *current;
    int listSize = getSize(path);
    current = getNth(path, 0)->element;
    while (current->id != 0) {
        prev = getNth(path, listSize - current->id)->element;
        printRobotsCommand(current, prev);
        *current = *prev;
    }
    while (!isEmpty()) {
        printf("%c\n", popCommand());
    }
}