cmake_minimum_required(VERSION 3.9)
project(ICFPC_2012 C)

set(CMAKE_C_STANDARD 11)

add_executable(ICFPC_2012 main.c loader.c solver.c localFinder.c headers/loader.h headers/cell.h headers/solver.h headers/localFinder.h linkedList.c headers/linkedList.h headers/element.h stack.c headers/stack.h queue.c headers/queue.h)