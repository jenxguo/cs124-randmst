#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "graph.hpp"
#include "randmst.hpp"
using namespace std;

float calcAvgWeight(int flag, int n, int trials, int d);
float getMSTWeight(int n, int d);

int main(int argc, char *argv[]) {
    //checks that there are command line args
    if (argc != 5)
    {
        printf("Usage: ./randmst 0 numpoints numtrials dimension\n");
        return 1;
    }

    int flag = (int) strtol(argv[1], NULL, 10);
    int numpoints = (int) strtol(argv[2], NULL, 10);
    int numtrials = (int) strtol(argv[3], NULL, 10);
    int dimension = (int) strtol(argv[4], NULL, 10);

    if (dimension != 0 && dimension != 2 && dimension != 3 && dimension != 4) {
        printf("Dimension must be 0, 2, 3, or 4.\n");
        return 1;
    }

    // seed rand
    srand (static_cast <unsigned> (time(0)));

    float avgWeight = calcAvgWeight(flag, numpoints, numtrials, dimension);

    printf("%f %i %i %i\n", avgWeight, numpoints, numtrials, dimension);

    ofstream myfile;
    myfile.open("data.txt", ofstream::app);
    myfile << numpoints << ", " << numtrials << ", " << dimension << ", " << avgWeight << endl;
    myfile.close();
    return 0;
}

float calcAvgWeight(int flag, int n, int trials, int d) {
    float totalWeight = 0;

    for (int i = 0; i < trials; i++) {
        totalWeight += getMSTWeight(n, d);
    }

    return totalWeight / trials;
}

float getMSTWeight(int n, int d) {
    // initialize graph
    int numEdges = (n * (n-1)) / 2;
    edge* graph = new edge[numEdges];

    // populate graph with edge objects
    Node* sets = createGraph(n, d, graph);

    // Test print Graph: feel free to comment out / remove later
    // for (int i = 0; i < numEdges; i++) {
    //     printf("%ith edge from vert %i to vert %i with weight %f\n", i, graph[i].v->val, graph[i].u->val, graph[i].weight);
    // }

    // generate MST
    float sumOfTotalMST = Kruskals(graph, n, numEdges);
    printf("sum of total mst %f\n", sumOfTotalMST);

    // destroy everything
    destroyGraph(numEdges, graph);
    delete[] graph;
    
    for (int i = 0; i < n; i++) {
        DESTROY(&sets[i]);
    }

    return sumOfTotalMST;
}