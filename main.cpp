#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>
#include "graph.hpp"
#include "randmst.hpp"
#include "unionfind.hpp"
#include <chrono>
using namespace std;

float calcAvgWeight(int flag, int n, int trials, int d);
float getMSTWeight(int n, int d);

int main(int argc, char *argv[]) {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::milliseconds;

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

    std::chrono::high_resolution_clock::time_point start = high_resolution_clock::now();
    float avgWeight = calcAvgWeight(flag, numpoints, numtrials, dimension);
    std::chrono::high_resolution_clock::time_point end = high_resolution_clock::now();

    printf("%f %i %i %i\n", avgWeight, numpoints, numtrials, dimension);

    duration<double, std::milli> ms_double = end - start;
    ofstream myfile;
    myfile.open("data.txt", ofstream::app);
    myfile << numpoints << ", " << numtrials << ", " << dimension << ", " << avgWeight << ", " << ms_double.count() << endl;
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

    // reseed rand
    srand (static_cast <unsigned> (time(0)));

    // generate random graph
    std::pair<int, edge* > res = createGraph(n, d);
    int numEdges = std::get<0>(res);
    edge* graph = std::get<1>(res);

    // generate MST
    float sumOfTotalMST = Kruskals(graph, n, numEdges);

    return sumOfTotalMST;
}