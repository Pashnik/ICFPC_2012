#ifndef ICFPC_2012_CELL_H
#define ICFPC_2012_CELL_H

enum cellType {
    ROBOT, STONE, CLOSED_OUT, GROUND, WALL, LAMBDA, OPENED_OUT, EMPTY
};

typedef struct cell {
    enum cellType type;
    int x;
    int y;
} Cell;

#endif //ICFPC_2012_CELL_H
