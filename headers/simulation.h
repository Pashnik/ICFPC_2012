#ifndef ICFPC_2012_SIMULATION_H
#define ICFPC_2012_SIMULATION_H

#include "solver.h"
#include "stack.h"

void selectCommand(Cell *first, Cell *second);

void reestablishPath(Node *returnPath, Cell **map, Node **lambdas, Cell *currentLambda);

int canMakeStep(Cell **map, Cell *cell);

void checkPath(Node *path, Cell **map, Cell *lambda, Node **lambdas);

void freeMap(Cell **map);

Cell **copyMap(Cell **map);

void makeStep(Cell **map, Cell *current);

void freeStack();

void simulate(Cell **map);

void getScore();

extern int mapHeight;

extern int mapWidth;

#endif //ICFPC_2012_SIMULATION_H
