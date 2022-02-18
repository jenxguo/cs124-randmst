#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include "graph.hpp"
#include "unionfind.hpp"
#include "randmst.hpp"

// void createGraph(int n, int d, edge*graph);
float generateEdgeWeight(int d);
float random01();

void createGraph(int n, int d, edge *graph) {
    int count = 0;

    Node* nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = MAKESET(i);
    }

    // generate edges from vertex i to vertex j
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            float weight = generateEdgeWeight(d);

            // add adj. matrix edge from i to j
            graph[count].v = nodes[i];
            graph[count].u = nodes[j];
            graph[count].weight = weight;

            count ++;
        }
    }

    /* Testing sort 
    printf("\n now we sort \n");

    MergeSort(graph, 0, numEdges-1);

    for (int i = 0; i < numEdges; i++) {
        printf("graph index %i edge from vert %i to vert %i with weight %f\n", i, graph[i].v->val, graph[i].u->val, graph[i].weight);
    }
    */
}

float generateEdgeWeight(int d) {
    // generate random weight between 0 and 1
    if (d == 0) {
        return random01();
    }
    // generate random weight in unit sq
    else if (d == 2)
    {
        float x1 = random01();
        float x2 = random01();
        float y1 = random01();
        float y2 = random01();
        return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
    }
    // generate random weight in unit cube
    else if (d == 3)
    {
        float x1 = random01();
        float x2 = random01();
        float y1 = random01();
        float y2 = random01();
        float z1 = random01();
        float z2 = random01();
        return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2));
    }
    // generate random weight in unit hypercube
    else if (d == 4)
    {
        float x1 = random01();
        float x2 = random01();
        float y1 = random01();
        float y2 = random01();
        float z1 = random01();
        float z2 = random01();
        float h1 = random01();
        float h2 = random01();
        return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2) + pow((z2 - z1), 2) + pow((h2 - h1), 2));
    }
    return 0;
}

float random01() {
    return (float) (rand()) / (float) (RAND_MAX);
}