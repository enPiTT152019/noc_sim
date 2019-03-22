#ifndef DEFS_H
#define DEFS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_ROUTERS 2
#define NUM_LINES   11
#define LENGTH      30

struct dataline
{
    int source[NUM_LINES];
    int target[NUM_LINES];
    int end[NUM_LINES];
    char **str;
};

struct processing_element
{
    int x, y, id;
};

struct processor
{
    int id;
    char **str;
};

struct message
{
    int destino_x, destino_y, origem_x, origem_y;
    char **str;
};

int qt_nodes_x, qt_nodes_y;
struct dataline data;
struct processor cpu;
pthread_t routers[NUM_ROUTERS], processors[NUM_ROUTERS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif