#include <stdlib.h>
#include "headers/cell.h"
#include "math.h"
#include "headers/solver.h"
#include "headers/finder.h"
#include "stdio.h"

#define START_SIZE 100

void start(Cell **map, const int *height, const int *width) {
    Node *lambdas = NULL;
    Robot *robot = (Robot *) malloc(sizeof(Robot));
    Wall *walls = (Wall *) malloc(START_SIZE * sizeof(Wall));
    Exit *exit = (Exit *) malloc(sizeof(Exit));
    setInitialInf(map, height, width, &lambdas, robot, walls, exit);

    //Test for finding the path to the shortest lambda!
    while (lambdas != NULL) {
        int nextLambda = findNextLambda(lambdas, robot);
        Lambda lambda = deleteNth(&lambdas, nextLambda);
        if (findShortestPath(robot, &lambda, map, height, width))
            lambdas = getNth(lambdas, 0);
        else {
            printf("A");
            break;
        }
    }

}

/*
 * This method finds the coordinates of all found lambdas, walls and robots and remembers them
 */

void setInitialInf(Cell **map, const int *height, const int *width,
                   Node **node, Robot *robot, Wall *walls, Exit *exit) {
    unsigned int currentWalls = 0, commonWalls = START_SIZE;
    for (int i = 0; i < *height; ++i) {
        for (int j = 0; j < *width; ++j) {
            if (map[i][j].type == LAMBDA) {
                Lambda current;
                current.x = map[i][j].x, current.y = map[i][j].y;
                push(node, current);
            }
            if (map[i][j].type == ROBOT)
                robot->x = map[i][j].x, robot->y = map[i][j].y;
            if (map[i][j].type == STONE) {
                walls[currentWalls].x = map[i][j].x, walls[currentWalls].y = map[i][j].y;
                if (currentWalls > commonWalls) {
                    commonWalls *= 2;
                    walls = realloc(walls, commonWalls * sizeof(Wall));
                }
                ++currentWalls;
            }
            if (map[i][j].type == CLOSED_OUT) exit->x = map[i][j].x, exit->y = map[i][j].y;
        }
    }
}

int findNextLambda(Node *node, Robot *robot) {
    double distance = START_SIZE, currentDistance = 0;
    int index = 0, currentIndex = 0;
    while (node != NULL) {
        currentDistance = sqrt(pow(robot->x - node->lambda.x, 2) + pow(robot->y - node->lambda.y, 2));
        if (currentDistance < distance) {
            distance = currentDistance;
            index = currentIndex;
        }
        node = node->next;
        ++currentIndex;
    }
    return index;
}