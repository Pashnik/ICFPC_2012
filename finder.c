#include <stdlib.h>
#include <math.h>
#include "headers/finder.h"
#include "headers/stack.h"
#include "stdio.h"
#include "headers/queue.h"
#include "headers/simulation.h"

#define NUM_OF_NEIGHBOURS 4
#define SIZE 100

/*
 * This method finds the shortest local path from point a to point b, using the algorithm A-STAR
 */

int findLocalPath(Cell *robot, Cell *lambda, Cell **map, Node **lambdas) {
    Node *closed = NULL; // items we've already reviewed
    Node *opened = NULL; //items required for viewing
    Node *path = NULL;
    Cell *neighbours = NULL;
    push(&opened, robot);
    robot->id = 0;
    int id = 1, newSize = SIZE;
    double *g = (double *) malloc(SIZE * (sizeof(double)));
    double *f = (double *) malloc(SIZE * sizeof(double));
    g[0] = 0;
    f[0] = distance(robot, lambda);
    while (opened != NULL) {
        if (id > newSize) {
            newSize += SIZE;
            g = (double *) realloc(g, newSize * sizeof(double));
            f = (double *) realloc(f, newSize * sizeof(double));
        }
        int minIndex = getMin(f, opened);
        Cell *current = (Cell *) malloc(sizeof(Cell));
        *current = deleteNth(&opened, minIndex);
        if (equalCoordinates(current, lambda)) {
            push(&path, current);
            robot->x = lambda->x;
            robot->y = lambda->y;
            reestablishPath(path, map, lambdas, lambda);
            free(g), free(f), free(neighbours), free(current);
            deleteList(&closed);
            return 1;
        }
        push(&closed, current);
        neighbours = getNeighbours(current, map);
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
    free(neighbours);
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

void makeWave(Cell **map, Cell *robot, Node **lambda) {
    Cell *neighbours = NULL;
    Node *closed = NULL;
    Node *queue = NULL;
    Cell *current = NULL;
    enqueue(&queue, robot);
    while (queue != NULL) {
        current = (Cell *) malloc(sizeof(Cell));
        *current = dequeue(&queue);
        if (!haveElement(closed, current)) {
            push(&closed, current);
            neighbours = getNeighbours(current, map);
            for (int i = 0; i < NUM_OF_NEIGHBOURS; ++i) {
                if (!haveElement(closed, &neighbours[i]) && canMove(&neighbours[i]))
                    enqueue(&queue, &neighbours[i]);
            }
            if (current->type == LAMBDA && !haveElement(*lambda, current))
                push(lambda, current);
        }
    }
    free(neighbours);
}