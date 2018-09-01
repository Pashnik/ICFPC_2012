#include <stdlib.h>
#include "headers/cell.h"
#include "headers/intellect.h"

struct lambda *getLambdas(struct cell **map, const unsigned int *height, const size_t *width) {
    unsigned int currentQt = 0, commonQt = 10;
    struct lambda *lambdas = (struct lambda *) malloc(commonQt * sizeof(struct lambda));
    for (int i = 0; i < *height; ++i) {
        for (int j = 0; j < *width; ++j) {
            if (map[i][j].type == LAMBDA) {
                lambdas[currentQt].x = map[i][j].x, lambdas[currentQt].y = map[i][j].y;
                if (currentQt > commonQt) {
                    commonQt *= 2;
                    lambdas = realloc(lambdas, commonQt * sizeof(struct lambda));
                }
                ++currentQt;
            }
        }
    }
    return lambdas;
}
