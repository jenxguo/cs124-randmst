#ifndef EDGE_H_
#define EDGE_H_
#include "unionfind.hpp"

typedef struct
{
    int v;
    int u;
    float weight;
}
edge;

void createGraph(int n, int d, edge *graph);

void destroyGraph(int numEdges, edge* graph);

#endif