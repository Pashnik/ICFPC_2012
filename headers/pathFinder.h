#ifndef ICFPC_2012_PATHFINDER_H
#define ICFPC_2012_PATHFINDER_H

#include "cell.h"
#include "intellect.h"

unsigned int equalCoordinates(struct cell cell1, struct lambda cell2);

struct cell *getNeighbours(struct cell cell);

unsigned int isPath(struct cell **map, struct cell *cell);

#endif //ICFPC_2012_PATHFINDER_H
