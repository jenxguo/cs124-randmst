#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "unionfind.hpp"
#include "graph.hpp"
#include "randmst.hpp"

/*
Ayana's TODO:
- sort out MakeSet error
- sort out errors when I run make in terminal
*/

void MergeSort(edge *graph, int l, int r);
void Merge(edge *graph, int l, int m, int r);

std::vector<float> Kruskals(edge *graph, int n, int numEdges){
    // X stores the weights of the edges in the MST
    std::vector<float> X;

    // Sort edges in ascending order
    MergeSort(graph, 0, numEdges-1);

    // Actual MST buidling phase
    for (int i = 0; i < numEdges; i++){
        Node* nodeV = graph[i].v;
        Node* nodeU = graph[i].u;
        if (FIND(nodeV) != FIND(nodeU)){
            X.push_back(graph[i].weight);
            UNION(nodeV, nodeU);
        };
    };

    return X;
};

void Merge(edge *graph, int l, int m, int r){
    int len1 = m - l + 1;
    int len2 = r - m;

    float L[len1], R[len2];

    for (int i = 0; i < len1; i++) {
        L[i] = graph[l + i].weight;
    }
    for (int j = 0; j < len2; j++) {
        R[j] = graph[m + 1 + j].weight;
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = l;

    while (i < len1 && j < len2) {
        if (L[i] <= R[j]) {
            graph[k].weight = L[i];
            i++;
        } else {
            graph[k].weight = R[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        graph[k].weight = L[i];
        i++;
        k++;
    }

    while (j < len2) {
        graph[k].weight = L[j];
        j++;
        k++;
    }
};

void MergeSort(edge *graph, int l, int r){
    if (l < r){
        int m = (l+r-1)/2;
        MergeSort(graph, l, m);
        MergeSort(graph, m+1, r);
        Merge(graph, l, m, r);
    };
};