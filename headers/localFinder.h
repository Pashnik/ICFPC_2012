#ifndef ICFPC_2012_PATHFINDER_H
#define ICFPC_2012_PATHFINDER_H

#include "solver.h"

int equalCoordinates(Element *start, Element *end);

Element *getNeighbours(Element *element);

int canMove(Cell **map, Element *cell);

double heuristic(Element *start, Element *end, int *hopeNumber);

int findShortestPath(Element *robot, Element *lambda,
                     Cell **map, const int *height, const int *width);

void printWay(const int *path, const unsigned int *hopes, const int *height, const int *width, Cell **map);

void printRobotsCommand(Element *prev, Element *current);

void rollBackIds(const int *height, const int *width, Cell **map);

Element getCellById(const int *height, const int *width, Cell **map, int id);

Node *getMin(Node *node, const double *f);

#endif //ICFPC_2012_PATHFINDER_H
