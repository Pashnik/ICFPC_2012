#include <stdlib.h>
#include "headers/cell.h"
#include "math.h"
#include "headers/solver.h"
#include "headers/finder.h"
#include "headers/queue.h"
#include "headers/simulation.h"
#include "stdio.h"


#define SIZE 100

void start(Cell **map) {
    Node *lambdas = NULL;
    Cell *robot = (Cell *) malloc(sizeof(Cell));
    Cell *wayOut = (Cell *) malloc(sizeof(Cell));
    setInitialInf(map, robot, wayOut);
    makeWave(map, robot, &lambdas);

    //try to pick up all of the lambdas
    while (lambdas != NULL) {
        int nextLambda = findNextLambda(lambdas, robot);
        Cell lambda = deleteLambda(&lambdas, nextLambda);
        if (findLocalPath(robot, &lambda, map, &lambdas))
            lambdas = getNth(lambdas, 0);
    }

    //heading to the exit if there is no lambda on the map
    if (!haveLambdas(map)) {
        if (!findLocalPath(robot, wayOut, map, &lambdas)) printf("A \n");
    } else printf("A \n");

    //show total score
    getScore();
}

/*
 * This method finds the coordinates of all found walls and robots and remembers them
 */

void setInitialInf(Cell **map, Cell *robot, Cell *wayOut) {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
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

Cell deleteLambda(Node **lambdas, int id) {
    return deleteNth(lambdas, id);
}

int haveLambdas(Cell **map) {
    for (int i = 0; i < mapHeight; ++i) {
        for (int j = 0; j < mapWidth; ++j) {
            if (map[i][j].type == LAMBDA)
                return 1;
        }
    }
    return 0;
}