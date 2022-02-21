#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <numeric>
#include "unionfind.hpp"
#include "graph.hpp"
#include "randmst.hpp"
#include <chrono>
#include <fstream>

void MergeSort(edge* graph, int l, int r);
void Merge(edge* graph, int l, int m, int r);
void QuickSort(edge* graph, int start, int end);
int partition(edge* graph, int start, int end);

float Kruskals(edge* graph, int n, int numEdges){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    // Array keeps track of whether each vertex is in the MST (validity)
    int validity[n];
    memset( validity, 0, n*sizeof(int) );

    std::chrono::high_resolution_clock::time_point kruskalstart = high_resolution_clock::now();

    // X stores the weights of the edges in the MST
    std::vector<float> X;

    // Sort edges in ascending order
    QuickSort(graph, 0, numEdges - 1);

    Node *nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = MAKESET(i);
    }

    // printf("\nPOST SORT\n");
    // // Test print Graph: feel free to comment out / remove later
    // for (int i = 0; i < numEdges; i++) {
    //     printf("%ith edge from vert %i to vert %i with weight %f\n", i, graph[i].v, graph[i].u, graph[i].weight);
    // }

    // printf("\nKRUSKALS\n");

    // Actual MST buidling phase
    int edgesAdded = 0;
    for (int i = 0; i < numEdges; i++){
        Node* nodeV = nodes[graph[i].v];
        Node* nodeU = nodes[graph[i].u];
        // printf("%ith iteration, root nodeV %i is %i, root nodeU %i is %i\n", i, nodeV->val, nodeV->parent->val, nodeU->val, nodeU->parent->val);
        if (FIND(nodeV) != FIND(nodeU)){
            X.push_back(graph[i].weight);
            // printf("edge (%i, %i) added\n", nodeV->val, nodeU->val);
            validity[nodeV->val] = 1;
            validity[nodeU->val] = 1;
            edgesAdded++;
            UNION(nodeV, nodeU);
        };
        if (edgesAdded == n - 1) {
            printf("break now\n");
            break;
        }
    }; 

    // printf("\nWEIGHTS IN MST\n");

    // for (int i = 0; i < X.size(); i++) {
    //     float p = X[i];
    //     // printf("%ith weight in X: %f\n", i, p);
    // }

    // destroy node
    for (int i = 0; i < n; i++) {
        DESTROY(nodes[i]);
    }

    std::chrono::high_resolution_clock::time_point kruskalend = high_resolution_clock::now();
    duration<double, std::milli> ms_double = kruskalend - kruskalstart;

    // Check the validity of the MST
    int missingVertices = 0;
    for (int i = 0; i < n; i++) {
        if (validity[i] == 0) {
            missingVertices++;
        }
    }

    std::ofstream myfile;
    myfile.open("data.txt", std::ofstream::app);
    myfile << ms_double.count() << ", " << missingVertices << ", ";
    myfile.close();

    // modify slightly to return largest edge
    // return X[X.size() - 1];
    return std::accumulate(X.begin(), X.end(), 0.0);
};

int partition(edge* graph, int start, int end){
    edge pivot = graph[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (graph[i].weight < pivot.weight) {
            count ++;
        }
    }

    int pivotIndex = start + count;
    std::swap(graph[pivotIndex], graph[start]);

    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (graph[i].weight <= pivot.weight) {
            i++;
        }
 
        while (graph[j].weight > pivot.weight) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            std::swap(graph[i++], graph[j--]);
        }
    }
 
    return pivotIndex;
};

void QuickSort(edge* graph, int start, int end){
    // QuickSort, while potentially slower, has on average the same
    // runtime as MergeSort. In addition, it's space complexity is
    // O(log n) on average to MergeSort's O(n)
    if (start >= end) {
        return;
    }

    int p = partition(graph, start, end);
    QuickSort(graph, start, p-1);
    QuickSort(graph, p+1, end);
};


void Merge(edge* graph, int l, int m, int r){
    int len1 = m - l + 1;
    int len2 = r - m;

    edge L[len1], R[len2];

    for (int i = 0; i < len1; i++) {
        L[i] = graph[l + i];
    }
    for (int j = 0; j < len2; j++) {
        R[j] = graph[m + 1 + j];
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = l;

    while (i < len1 && j < len2) {
        if (L[i].weight <= R[j].weight) {
            graph[k] = L[i];
            i++;
        } else {
            graph[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        graph[k] = L[i];
        i++;
        k++;
    }

    while (j < len2) {
        graph[k] = R[j];
        j++;
        k++;
    }
};

void MergeSort(edge* graph, int l, int r){
    if (l < r){
        int m = l + (r - l) / 2;
        MergeSort(graph, l, m);
        MergeSort(graph, m+1, r);
        Merge(graph, l, m, r);
    };
};