#ifndef ICFPC_2012_INTELLECT_H
#define ICFPC_2012_INTELLECT_H

void makeMove(struct cell **map, const int *height, const int *width);

struct lambda {
    int x;
    int y;
};

struct robot {
    int x;
    int y;
} robot;

struct wall {
    int x;
    int y;
};

struct exit {
    int x;
    int y;
} out;

void setInitialInf(struct cell **map, const int *height, const int *width,
                   struct lambda *lambdas, struct robot *robot, struct wall *walls, struct exit *out);

int findNextLambda(struct lambda *lambdas, struct robot *robot, const int *quantity);

int getLambdaQuantity(const int *height, const int *width, struct cell **map);

struct cell getCellbyId(int id, struct cell **map, const int *height, const int *width);

#endif //ICFPC_2012_INTELLECT_H
