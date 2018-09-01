#ifndef ICFPC_2012_INTELLECT_H
#define ICFPC_2012_INTELLECT_H

struct lambda *getLambdas(struct cell **map, const unsigned int *height, const size_t *width);

struct lambda {
    unsigned int x;
    unsigned int y;
};

#endif //ICFPC_2012_INTELLECT_H
