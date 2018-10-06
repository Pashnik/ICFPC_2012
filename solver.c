#include <stdlib.h>
#include "headers/cell.h"
#include "math.h"
#include "headers/solver.h"
#include "headers/localFinder.h"
#include "headers/queue.h"
#include "stdio.h"

#define SIZE 100

void start(Cell **map) {
    Node *lambdas = NULL;
    Node *stones = NULL;
    Cell *robot = (Cell *) malloc(sizeof(Cell));
    Cell *wayOut = (Cell *) malloc(sizeof(Cell));
    setInitialInf(map, &lambdas, robot, &stones, wayOut);
    makeWave(map, robot, &lambdas);

    //Test for finding the path to the shortest lambda!
    while (lambdas != NULL) {
        int nextLambda = findNextLambda(lambdas, robot);
        Cell lambda = deleteNth(&lambdas, nextLambda);
        if (findShortestPath(robot, &lambda, map))
            lambdas = getNth(lambdas, 0);
    }
}

/*
 * This method finds the coordinates of all found lambdas, walls and robots and remembers them
 */

void setInitialInf(Cell **map, Node **lambda, Cell *robot, Node **stone, Cell *wayOut) {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            //if (map[i][j].type == LAMBDA) push(lambda, &map[i][j]);

            if (map[i][j].type == STONE) push(stone, &map[i][j]);

            if (map[i][j].type == CLOSED_OUT) wayOut->x = map[i][j].x, wayOut->y = map[i][j].y;
            if (map[i][j].type == ROBOT) robot->x = map[i][j].x, robot->y = map[i][j].y;
        }
    }
}

int findNextLambda(Node *node, Cell *robot) {
    double distance = SIZE, currentDistance = 0;
    int index = 0, currentIndex = 0;
    while (node != NULL) {
        currentDistance = sqrt(pow(robot->x - node->cell->x, 2) + pow(robot->y - node->cell->y, 2));
        if (currentDistance < distance) {
            distance = currentDistance;
            index = currentIndex;
        }
        node = node->next;
        ++currentIndex;
    }
    return index;
}

void makeWave(Cell **map, Cell *robot, Node **lambda) {
    Node *closed = NULL;
    Node *queue = NULL;
    enqueue(&queue, robot);
    while (queue != NULL) {
        Cell *current = (Cell *) malloc(sizeof(Cell));
        *current = dequeue(&queue);
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
