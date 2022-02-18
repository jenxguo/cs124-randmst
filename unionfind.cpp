#include <stdio.h>
#include <stdlib.h>
#include "unionfind.hpp"

// struct Node {
//     int val;
//     int rank;
//     Node *parent;
// };

/* Create a new set */
Node* MAKESET(int i){
    Node* vertex = new Node();
    vertex->val = i;
    vertex->parent = vertex;
    vertex->rank = 0;
    return vertex;
};

/* Find and return the root of a node */
Node* FIND(Node* node){
    Node* original = node;
    while ( node->parent != node ){
        node = node->parent;
    };
    original->parent = node; // Reassign original node's parent to root
    return node;
};

/* Link two roots together. Return the root of the combined tree. */
Node* LINK(Node* root1, Node* root2){
    if (root1->rank > root2->rank) {
        root2->parent = root1;
        return root1;
    }
    else if (root2->rank > root1->rank) {
        root1->parent = root2;
        return root2;
    }
    else {
        root1->parent = root2;
        root2->rank++;
        return root2;
    };
};

/* Join two trees together. Return root of final tree. */
Node* UNION(Node* node1, Node* node2){
    Node* root1 = FIND(node1);
    Node* root2 = FIND(node2);
    return LINK(root1, root2);
};

/* Frees memory of set. */
void DESTROY(Node* node){
    delete node;
}