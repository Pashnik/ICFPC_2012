cmake_minimum_required(VERSION 3.9)
project(ICFPC_2012 C)

set(CMAKE_C_STANDARD 11)

add_executable(ICFPC_2012 main.c launcher.c solver.c localFinder.c headers/launcher.h headers/cell.h headers/solver.h headers/localFinder.h structures/linkedList.c headers/linkedList.h structures/stack.c headers/stack.h structures/queue.c headers/queue.h)