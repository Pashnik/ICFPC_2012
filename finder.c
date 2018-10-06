#include <stdlib.h>
#include <math.h>
#include "headers/finder.h"
#include "headers/stack.h"
#include "stdio.h"
#include "headers/queue.h"

#define NUM_OF_NEIGHBOURS 4
#define SIZE 200

/*
 * This method finds the shortest local path from point a to point b, using the algorithm A-STAR
 */

int findShortestPath(Cell *robot, Cell *lambda, Cell **map, Node **lambdas) {
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
        Cell *current = (Cell *) malloc(sizeof(Cell));
        *current = deleteNth(&opened, minIndex);
        if (equalCoordinates(current, lambda)) {
            push(&path, current);
            reestablishPath(path, map, lambdas);
            robot->x = lambda->x;
            robot->y = lambda->y;
            return 1;
        }
        push(&closed, current);
        Cell *neighbours = getNeighbours(current, map);
        for (int i = 0; i < NUM_OF_NEIGHBOURS; ++i) {
            if (!haveElement(closed, &neighbours[i]) && canMove(&neighbours[i])) {
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

Cell *getNeighbours(Cell *cell, Cell **map) {
    Cell *neighbours = (Cell *) malloc(NUM_OF_NEIGHBOURS * sizeof(Cell));
    neighbours[0] = map[cell->y + 1][cell->x];
    neighbours[1] = map[cell->y - 1][cell->x];
    neighbours[2] = map[cell->y][cell->x + 1];
    neighbours[3] = map[cell->y][cell->x - 1];
    return neighbours;
}

int equalCoordinates(Cell *start, Cell *end) {
    if (start->x == end->x && start->y == end->y) return 1;
    return 0;
}

double distance(Cell *start, Cell *end) {
    return sqrt(pow(start->x - end->x, 2) + pow(start->y - end->y, 2));
}

int canMove(Cell *cell) {
    if (cell->type == GROUND || cell->type == LAMBDA || cell->type == EMPTY) return 1;
    return 0;
}

void printRobotsCommand(Cell *first, Cell *second) {
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

void reestablishPath(Node *path, Cell **map, Node **lambdas) {
    int counter = 0;
    Cell *prev;
    Cell *current;
    int listSize = getSize(path);
    current = getNth(path, 0)->cell;
    while (current->id != 0) {
        if (current->type == LAMBDA && counter != 0) {
            int index = getIndex(*lambdas, current);
            deleteLambda(lambdas, index);
        }
        map[current->y][current->x].type = EMPTY;
        prev = getNth(path, listSize - current->id)->cell;
        printRobotsCommand(current, prev);
        *current = *prev;
        ++counter;
    }
    while (!isEmpty()) {
        printf("%c\n", popCommand());
    }
}

void makeWave(Cell **map, Cell *robot, Node **lambda) {
    Node *closed = NULL;
    Node *queue = NULL;
    enqueue(&queue, robot);
    while (queue != NULL) {
        Cell *current = (Cell *) malloc(sizeof(Cell));
        *current = dequeue(&queue);
        if (!haveElement(closed, current)) {
            push(&closed, current);
            Cell *neighbours = getNeighbours(current, map);
            for (int i = 0; i < 4; ++i) {
                if (!haveElement(closed, &neighbours[i]) && canMove(&neighbours[i]))
                    enqueue(&queue, &neighbours[i]);
            }
            if (current->type == LAMBDA && !haveElement(*lambda, current))
                push(lambda, current);
        }
    }
}