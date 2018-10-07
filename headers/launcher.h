#ifndef ICFPC_2012_LOADER_H
#define ICFPC_2012_LOADER_H

#include "cell.h"

Cell **setCells(char **array);

int getWidth(char **array);

void launch(char *fileName);

void freeArray(char **array);

int mapHeight;

int mapWidth;

#endif //ICFPC_2012_LOADER_H
