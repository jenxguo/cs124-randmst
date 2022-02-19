#ifndef EDGE_H_
#define EDGE_H_
#include "unionfind.hpp"

typedef struct
{
    Node* v;
    Node* u;
    float weight;
}
edge;

Node* createGraph(int n, int d, edge *graph);

void destroyGraph(int numEdges, edge* graph);

#endif