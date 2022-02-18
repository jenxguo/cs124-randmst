#ifndef RANDMST_H_
#define RANDMST_H_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "graph.hpp"


std::vector<float> Kruskals(edge *graph, int n, int numEdges);

#endif