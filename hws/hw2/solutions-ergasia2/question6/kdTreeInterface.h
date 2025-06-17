/**
 * @file kdTreeInterface.h
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief kd Tree Data Structure Interface
*/

#ifndef KD_TREE_INTERFACE_H
#define KD_TREE_INTERFACE_H

#define EMPTY 10000

#include "PointInterface.h"
#include "RangeInterface.h"
#include "ListInterface.h"

typedef enum node_type {
    VERTICAL_LINE, HORIZONTAL_LINE, LEAF_NODE
} NodeType;

typedef struct kdnode {
    // The point stored in this node
    // only for leaf nodes
    Point * point;

    // Value for line - NULL on leaf nodes
    double line;

    // VERTICAL_LINE if Vertical Line (x-axis)
    // HORIZONTAL_LINE if Horizontal Line(y-axis)
    // LEAF_NODE if Leaf Node
    NodeType type;

    struct kdnode * left; // Left subtree

    struct kdnode * right; // Right subtree
} KDNode;

void printVisualTree(KDNode *, int, const char *);

KDNode * kdnode_init(Point *, double, NodeType);

KDNode * buildKDTree(Point **, int, int);
   
void searchKDTree(KDNode *, Range *, Range *, List);

void destroyKDTree(KDNode *);

#endif