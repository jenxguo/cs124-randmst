#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <random>
#include <vector>
#include "graph.hpp"
#include "unionfind.hpp"
#include "randmst.hpp"

// void createGraph(int n, int d, edge*graph);
float random01();
float findThreshold(int n, int d);

std::pair<int, edge* > createGraph(int n, int d) {
    // int numEdges = (n+1)*(n)/2;
    // edge **graph = malloc(cap * sizeof(edge*));
    int lenGraph = n;
    edge* graph = (edge*) malloc(lenGraph * sizeof(edge));
    int count = 0;

    float threshold = findThreshold(n, d);

    if (d == 0) {
        // generate edges from vertex i to vertex j
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                edge e;
                float weight = random01();
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

    } else {
        // generate vertex positions
        float vertexPositions[n][d];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < d; j++) {
                vertexPositions[i][j] = random01();
            }
        }

         // generate edges from vertex i to vertex j
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                edge e;

                // find edge weight using distance formula
                float weight = 0;
                for (int k = 0; k < d; k++) {
                    weight += pow(vertexPositions[i][k] - vertexPositions[j][k], 2);
                }
                weight = sqrt(weight);

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

// void destroyGraph(int numEdges, edge* graph) {

//     for (int i = 0; i < numEdges; i++) {
//         printf("trying to free edge from %i to %i wit weight %f\n", graph[i].v, graph[i].u, graph[i].weight);
//         delete &(graph[i]);
//         printf("freed\n");
//     }
// }

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
            return 0.08;
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