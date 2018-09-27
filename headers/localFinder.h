#ifndef ICFPC_2012_PATHFINDER_H
#define ICFPC_2012_PATHFINDER_H

#include "solver.h"

int equalCoordinates(Element *start, Element *end);

Element *getNeighbours(Element *element);

int canMove(Cell **map, Element *cell);


int findShortestPath(Element *robot, Element *lambda,
                     Cell **map);


void printRobotsCommand(Element *prev, Element *current);


double distance(Element *start, Element *end);

void reestablishPath(Node *path);

#endif //ICFPC_2012_PATHFINDER_H

