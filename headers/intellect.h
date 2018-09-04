#ifndef ICFPC_2012_INTELLECT_H
#define ICFPC_2012_INTELLECT_H

void makeMove(struct cell **map, const unsigned int *height, const unsigned int *width);

struct lambda {
    unsigned int x;
    unsigned int y;
};

struct robot {
    unsigned int x;
    unsigned int y;
} robot;

struct wall {
    unsigned int x;
    unsigned int y;
};

struct exit {
    unsigned int x;
    unsigned int y;
} out;

void setInitialInf(struct cell **map, const unsigned int *height, const unsigned int *width,
                   struct lambda *lambdas, struct robot *robot, struct wall *walls, struct exit *out);

int findNextLambda(struct lambda *lambdas, struct robot *robot);

#endif //ICFPC_2012_INTELLECT_H
