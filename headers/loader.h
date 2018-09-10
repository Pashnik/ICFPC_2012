#ifndef ICFPC_2012_LOADER_H
#define ICFPC_2012_LOADER_H

#include "cell.h"

Cell **setCells(char **array, const int *height, const int *width);

int getWidth(char **array, const int *height);

void load(char *fileName);

#endif //ICFPC_2012_LOADER_H
