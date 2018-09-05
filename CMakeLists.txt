cmake_minimum_required(VERSION 3.9)
project(ICFPC_2012 C)

set(CMAKE_C_STANDARD 11)

add_executable(ICFPC_2012 main.c loader.c intellect.c pathFinder.c headers/loader.h headers/cell.h headers/intellect.h headers/pathFinder.h)