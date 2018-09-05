#ifndef ICFPC_2012_CELL_H
#define ICFPC_2012_CELL_H

enum cellType {
    ROBOT, STONE, CLOSED_OUT, GROUND, WALL, LAMBDA, OPENED_OUT, EMPTY
};

struct cell {
    enum cellType type;
    unsigned int x;
    unsigned int y;
    unsigned int id;
    unsigned int neighbourId;
};

#endif //ICFPC_2012_CELL_H
