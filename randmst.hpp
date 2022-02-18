#ifndef RANDMST_H_
#define RANDMST_H_
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "graph.hpp"


float Kruskals(edge *graph, int n, int numEdges);

void MergeSort(edge *graph, int l, int r);

#endif