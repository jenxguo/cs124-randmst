#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "graph.hpp"

float calcAvgWeight(int flag, int n, int trials, int d);

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

    // seed rand
    srand (static_cast <unsigned> (time(0)));

    float avgWeight = calcAvgWeight(flag, numpoints, numtrials, dimension);

    printf("%f %i %i %i\n", avgWeight, numpoints, numtrials, dimension);

    return 0;
}

float calcAvgWeight(int flag, int n, int trials, int d) {
    float totalWeight = 0;

    for (int i = 0; i < trials; i++) {

        // create graph
        int numEdges = (n * (n-1)) / 2;
        edge graph[numEdges];
        createGraph(n, d, graph);

        // generate MST
    }

    return totalWeight / trials;
}