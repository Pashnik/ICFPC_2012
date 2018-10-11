#include <stdlib.h>
#include "headers/launcher.h"

int main(int argc, char **argv) {
    if (argc != 2) exit(-1);
    char *name = argv[1];
    launch(name);
    return 0;
}