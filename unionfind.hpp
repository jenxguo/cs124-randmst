#ifndef NODE_H_
#define NODE_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    int rank;
    struct Node *parent;
} Node;

/* Create a new set */
Node* MAKESET(int i);

/* Find and return the root of a node */
Node* FIND(Node* node);

/* Link two roots together. Return the root of the combined tree. */
Node* LINK(Node* root1, Node* root2);

/* Join two trees together. Return root of final tree. */
Node* UNION(Node* node1, Node* node2);

/* Frees memory of set. */
void DESTROY(Node* node);

#endif