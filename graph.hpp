#ifndef EDGE_H_
#define EDGE_H_

#include "unionfind.hpp"
#include <vector>

typedef struct
{
    int v;
    int u;
    float weight;
}
edge;

std::pair<int, edge* > createGraph(int n, int d);

void destroyGraph(int numEdges, edge* graph);

#endif