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

    // initially malloc space for graph of size n
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
                // remalloc, increase size of graph array if need be
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

        // array to ensure validity
        int validity[n];
        memset( validity, 0, n*sizeof(int) );

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
}

float random01() {
    return (float) (rand()) / (float) (RAND_MAX);
}

float findThreshold(int n, int d) {
    if (n < 2000) {
        return 1;
    }
    else if (n > 150000) {
        if (d == 0) {
            return 0.000015;
        }
        else if (d == 2) {
            return 0.005;
        }
        else if (d == 3) {
            return 0.027;
        }
        else if (d == 4) {
            return 0.07; // 0.05
        }
    }
    else if (n > 70000) {
        if (d == 0) {
            return 0.00007;
        }
        else if (d == 2) {
            return 0.005;
        }
        else if (d == 3) {
            return 0.027;
        }
        else if (d == 4) {
            return 0.07; // 0.05
        }
    }
    else if (n > 50000) {
        if (d == 0) {
            return 0.0002;
        }
        else if (d == 2) {
            return 0.008;
        }
        else if (d == 3) {
            return 0.04;
        }
        else if (d == 4) {
            return 0.08;
        }
    }
    else if (d == 0) {
        float safety = 1000/n;
        return (1.65 * pow(n, -0.769)) + safety;
    }
    else if (d == 2) {
        float safety = 1000/n;
        return (0.941 * pow(n, -0.423)) + safety;
    }
    else if (d == 3) {
        float safety = 1000/n;
        return (0.923 * pow(n, -0.283)) + safety;
    }
    else if (d == 4) {
        float safety = 0.003;
        return (1.07 * pow(n, -0.236)) + safety;
    }
    return 1;
}