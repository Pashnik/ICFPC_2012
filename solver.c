#include <stdlib.h>
#include "headers/cell.h"
#include "math.h"
#include "headers/solver.h"
#include "headers/localFinder.h"
#include "headers/queue.h"
#include "stdio.h"

#define SIZE 100

void start(Cell **map, const int *height, const int *width) {
    Node *lambdas = NULL;
    Node *stones = NULL;
    Element *robot = (Element *) malloc(sizeof(Element));
    Element *exit = (Element *) malloc(sizeof(Element));
    setInitialInf(map, height, width, &lambdas, robot, &stones, exit);

    //Test for finding the path to the shortest lambda!
    while (lambdas != NULL) {
        int nextLambda = findNextLambda(lambdas, robot);
        Element lambda = deleteNth(&lambdas, nextLambda);
        if (findShortestPath(robot, &lambda, map))
            lambdas = getNth(lambdas, 0);
    }
}

/*
 * This method finds the coordinates of all found lambdas, walls and robots and remembers them
 */

void setInitialInf(Cell **map, const int *height, const int *width,
                   Node **lambda, Element *robot, Node **stone, Element *exit) {
    for (int i = 0; i < *height; ++i) {
        for (int j = 0; j < *width; ++j) {
            Element *current = (Element *) malloc(sizeof(Element));
            if (map[i][j].type == LAMBDA) {
                current->x = map[i][j].x, current->y = map[i][j].y;
                push(lambda, current);
            }
            if (map[i][j].type == STONE) {
                current->x = map[i][j].x, current->y = map[i][j].y;
                push(stone, current);
            }
            if (map[i][j].type == CLOSED_OUT) exit->x = map[i][j].x, exit->y = map[i][j].y;
            if (map[i][j].type == ROBOT) robot->x = map[i][j].x, robot->y = map[i][j].y;
        }
    }
}

int findNextLambda(Node *node, Element *robot) {
    double distance = SIZE, currentDistance = 0;
    int index = 0, currentIndex = 0;
    while (node != NULL) {
        currentDistance = sqrt(pow(robot->x - node->element->x, 2) + pow(robot->y - node->element->y, 2));
        if (currentDistance < distance) {
            distance = currentDistance;
            index = currentIndex;
        }
        node = node->next;
        ++currentIndex;
    }
    return index;
}

void makeWave(Cell **map, const int *height, const int *width, Element *robot) {
    Node *queue = NULL;
    enqueue(&queue, robot);
    while (queue != NULL) {
        /*??????*/
    }
}
