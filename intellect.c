#include <stdlib.h>
#include <limits.h>
#include "headers/cell.h"
#include "math.h"
#include "headers/intellect.h"


#define START_SIZE 100

void makeMove(struct cell **map, const unsigned int *height, const unsigned int *width) {
    struct lambda *lambdas = (struct lambda *) malloc(START_SIZE * sizeof(struct lambda));
    struct wall *walls = (struct wall *) malloc(START_SIZE * sizeof(struct wall));
    setInitialInf(map, height, width, lambdas, &robot, walls, &out);
    //Test for finding the path to the shortest lambda!


}

/*
 * This method finds the coordinates of all found lambdas, walls and robots and remembers them
 */

void setInitialInf(struct cell **map, const unsigned int *height, const unsigned int *width,
                   struct lambda *lambdas, struct robot *robot, struct wall *walls, struct exit *out) {
    unsigned int currentLambdas = 0, commonLambdas = START_SIZE;
    unsigned int currentWalls = 0, commonWalls = START_SIZE;
    for (int i = 0; i < *height; ++i) {
        for (int j = 0; j < *width; ++j) {
            if (map[i][j].type == LAMBDA) {
                lambdas[currentLambdas].x = map[i][j].x, lambdas[currentLambdas].y = map[i][j].y;
                if (currentLambdas > commonLambdas) {
                    commonLambdas *= 2;
                    lambdas = realloc(lambdas, commonLambdas * sizeof(struct lambda));
                }
                ++currentLambdas;
            }
            if (map[i][j].type == ROBOT) (*robot).x = map[i][j].x, (*robot).y = map[i][j].y;
            if (map[i][j].type == WALL) {
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

int findNextLambda(struct lambda *lambdas, struct robot *robot, unsigned int quantity) {
    double distance = SHRT_MAX, currentDistance = 0;
    int index = 0;
    for (int i = 0; i < quantity; ++i) {
        currentDistance = sqrt(pow((*robot).x - lambdas[i].x, 2) + pow((*robot).y - lambdas[i].y, 2));
        if (currentDistance < distance) {
            distance = currentDistance;
            index = i;
        }
    }
    return index;
}


// Very bad. Think about it!
unsigned int getLambdaQuantity(const unsigned int *height, const unsigned int *width, struct cell **map) {
    unsigned int counter = 0;
    for (int i = 0; i < *height; ++i) {
        for (int j = 0; j < *width; ++j) {
            if (map[i][j].type == LAMBDA) ++counter;
        }
    }
    return counter;
}

