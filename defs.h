#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define LENGTH      30

struct dataline
{
    int *source;
    int *target;
    int *end;
    char **str;
};

struct processing_element
{
    int *x, *y, *id;
};

int num_lines, qt_nodes_x, qt_nodes_y, num_routers, aux_x, aux_y;
#endif