#ifndef ICFPC_2012_PATHFINDER_H
#define ICFPC_2012_PATHFINDER_H

#include "solver.h"

int equalCoordinates(Cell *start, Cell *end);

Cell *getNeighbours(Cell *cell, Cell **map);

int canMove(Cell *cell);


int findShortestPath(Cell *robot, Cell *lambda,
                     Cell **map, Node **lambdas);

void makeWave(Cell **map, Cell *robot, Node **lambda);

void printRobotsCommand(Cell *first, Cell *second);


double distance(Cell *start, Cell *end);

void reestablishPath(Node *path, Cell **map, Node **lambdas);

extern int mapHeight;

extern int mapWidth;

#endif //ICFPC_2012_PATHFINDER_H

