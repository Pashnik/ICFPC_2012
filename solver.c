#include <stdlib.h>
#include "headers/cell.h"
#include "math.h"
#include "headers/solver.h"
#include "headers/finder.h"


#define START_SIZE 100

void start(struct cell **map, const int *height, const int *width) {
    Node *node = NULL;
    struct wall *walls = (struct wall *) malloc(START_SIZE * sizeof(struct wall));
    setInitialInf(map, height, width, &node, &robot, walls, &out);
    Node *first = node;

    //Test for finding the path to the shortest lambda!
    while (node != NULL) {
        struct lambda lambda;
        int nextLambda = findNextLambda(node, &robot);
        lambda = deleteNth(&node, nextLambda);
        if (findShortestPath(&robot, &lambda, map, height, width)) node = first;
        else node = node->next;
    }
}

/*
 * This method finds the coordinates of all found lambdas, walls and robots and remembers them
 */

void setInitialInf(struct cell **map, const int *height, const int *width,
                   Node **node, struct robot *robot, struct wall *walls, struct exit *out) {
    unsigned int currentWalls = 0, commonWalls = START_SIZE;
    for (int i = 0; i < *height; ++i) {
        for (int j = 0; j < *width - 1; ++j) {
            if (map[i][j].type == LAMBDA) {
                struct lambda current;
                current.x = map[i][j].x, current.y = map[i][j].y;
                push(node, current);
            }
            if (map[i][j].type == ROBOT)
                (*robot).x = map[i][j].x, (*robot).y = map[i][j].y;
            if (map[i][j].type == STONE) {
                walls[currentWalls].x = map[i][j].x, walls[currentWalls].y = map[i][j].y;
                if (currentWalls > commonWalls) {
                    commonWalls *= 2;
                    walls = realloc(walls, commonWalls * sizeof(struct wall));
                }
                ++currentWalls;
            }
            if (map[i][j].type == CLOSED_OUT) (*out).x = map[i][j].x, (*out).y = map[i][j].y;
        }
    }
}

int findNextLambda(Node *node, struct robot *robot) {
    double distance = START_SIZE, currentDistance = 0;
    int index = 0, currentIndex = 0;
    while (node != NULL) {
        currentDistance = sqrt(pow((*robot).x - node->lambda.x, 2) + pow((*robot).y - node->lambda.y, 2));
        if (currentDistance < distance) {
            distance = currentDistance;
            index = currentIndex;
        }
        node = node->next;
        ++currentIndex;
    }
    return index;
}

struct cell getLambdaById(int id, struct cell **map, const int *height, const int *width) {
    struct cell failure;
    failure.x = -1, failure.y = -1;
    for (int i = 0; i < *height; ++i) {
        for (int j = 0; j < *width - 1; ++j) {
            if (map[i][j].id == id) return map[i][j];
        }
    }
    return failure;
}

