#include <stdlib.h>
#include "../headers/stack.h"

#define STACK_VAL 100 // stack length

int sp = 0;
char command[STACK_VAL]; // numbers stack

void pushCommand(char value) {
    if (sp < STACK_VAL) command[sp++] = value;
    else exit(-1);
}

int popCommand(void) {
    if (sp >= 0) return command[--sp];
    else exit(-1);
}

int isEmpty(void) {
    if (sp > 0) return 0;
    else return 1;
}
