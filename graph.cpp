#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <vector>
#include "graph.hpp"
#include "unionfind.hpp"
#include "randmst.hpp"

// void createGraph(int n, int d, edge*graph);
float generateEdgeWeight(int d);
float random01();
float findThreshold(int n, int d);

std::pair<int, edge* > createGraph(int n, int d) {
    // int numEdges = (n+1)*(n)/2;
    // edge **graph = malloc(cap * sizeof(edge*));
    int lenGraph = n;
    edge* graph = (edge*) malloc(lenGraph * sizeof(edge));
    int count = 0;

    float threshold = findThreshold(n, d);

    // generate edges from vertex i to vertex j
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            edge e;

            float weight = generateEdgeWeight(d);

            if (weight < threshold) {
                // add adj. matrix edge from i to j
                e.v = i;
                e.u = j;
                e.weight = weight;

                graph[count] = e;

                count++;
            }

            // remalloc, increase size of graph array if need to
            if (count >= lenGraph) {
                graph = (edge*) realloc((void*) graph, (lenGraph * 2) * sizeof(edge));
                lenGraph *= 2;
            }
        }
    }

    return std::make_pair(count, graph);

    /* Testing sort 
    printf("\n now we sort \n");

    MergeSort(graph, 0, numEdges-1);

    for (int i = 0; i < numEdges; i++) {
        printf("graph index %i edge from vert %i to vert %i with weight %f\n", i, graph[i].v->val, graph[i].u->val, graph[i].weight);
    }
    */
}

void destroyGraph(int numEdges, edge* graph) {

    for (int i = 0; i < numEdges; i++) {
        printf("trying to free edge from %i to %i wit weight %f\n", graph[i].v, graph[i].u, graph[i].weight);
        delete &(graph[i]);
        printf("freed\n");
    }
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

float findThreshold(int n, int d) {
    if (n < 20) {
        return 1;
    }
    else if (n > 50000) {
        if (d == 0) {
            return 0.00005;
        }
        else if (d == 2) {
            return 0.005;
        }
        else if (d == 3) {
            return 0.1;
        }
        else if (d == 4) {
            return 0.2;
        }
    }
    else if (d == 0) {
        float safety = 2/n;
        return (1.65 * pow(n, -0.769)) + safety;
    }
    else if (d == 2) {
        float safety = 2/n;
        return (0.941 * pow(n, -0.423)) + safety;
    }
    else if (d == 3) {
        float safety = 2/n;
        return (0.923 * pow(n, -0.283)) + safety;
    }
    else if (d == 4) {
        float safety = 2/n;
        return (1.07 * pow(n, -0.236)) + safety;
    }
    return 1;
}