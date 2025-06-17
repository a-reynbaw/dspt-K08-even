/**
 * @file kdTreeImplementation.c
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief kd Tree Data Structure Implementaion
*/

#ifndef KD_TREE_IMPLEMENTATION_C
#define KD_TREE_IMPLEMENTATION_C

// for memory allocation
#include <stdlib.h>
// for stdout and stderr use
#include <stdio.h>
// for function ceil
#include <math.h>
// all implemented header files in this directory
#include "kdTreeInterface.h"
#include "PointInterface.h"
#include "RangeInterface.h"
#include "ListInterface.h"

/* ------------------------------ HELPER FUNCTIONS ------------------------------ */
void printVisualTree(KDNode * node, int level, const char * prefix) {
    if (node != NULL) {
        // Print indentation and node value
        for (int i = 0; i < level * 4; i++) printf(" ");
        if (node->type == LEAF_NODE) {
            printf("%s(%f, %f)\n", prefix, node->point->x, node->point->y);
        } else {
            printf("%s%lf\n", prefix, node->line);
        }
        
        // Print left and right children
        if (node->left || node->right) {
            if (node->left) {
                printVisualTree(node->left, level + 1, "L--- ");
            } else {
                for (int i = 0; i < (level + 1) * 4; i++) printf(" ");
                printf("L--- None\n");
            }
            
            if (node->right) {
                printVisualTree(node->right, level + 1, "R--- ");
            } else {
                for (int i = 0; i < (level + 1) * 4; i++) printf(" ");
                printf("R--- None\n");
            }
        }
    }
}

/**
 * @brief Function to report all points in a subtree
 * @param node The root of the subtree
 * @param l List to store the results
 * @return -
*/
void ReportSubtree(KDNode * node, List l) {
    if (node != NULL) {
        // Print indentation and node value
        if (node->type == LEAF_NODE) {
            AddFirst(l, node->point);
        } else {
            ReportSubtree(node->left, l);
            ReportSubtree(node->right, l);
        }
    }
}

/* ------------------------------ CORE FUNCTIONS ------------------------------ */

/**
 * @brief Function to create a KDNode
 * @param p
 * @param line
 * @param type
 * @return A pointer to the KDNode created
 */
KDNode * kdnode_init(Point * p, double line, NodeType type) {
    // allocate space for the new node
    KDNode * NewNode = (KDNode *)malloc(sizeof(struct kdnode));

    if (!NewNode) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // set the NewNode type based on the given one
    NewNode->type = type;
    
    // init the next fields
    if (type == LEAF_NODE) {
        // if it's a leaf node, store the point and 
        // set to EMPTY the line field
        // NewNode->point->x = p->x;
        // NewNode->point->y = p->y;
        NewNode->point = point_init(p->x, p->y);

        if (!NewNode->point) {
            free(NewNode);
            return NULL;
        }

        NewNode->line = EMPTY;
    } else {
        //otherwise, set to NULL the point field
        // and init the line field
        NewNode->point = NULL;
        /**TODO: MAKE SURE THIS DEREFERENCE DOESN'T CAUSE PROBLEMS */
        NewNode->line = line;
    }

    // finally, init the pointer to children fields
    NewNode->left = NULL;
    NewNode->right = NULL;

    return NewNode;
}

/**
 * @brief Function to build a KDTree
 * @param points the set of points that bellong in the current subtree
 * @param n the number of points in 'points'
 * @param depth Depth of the current level. Should ALWAYS be 0 when calling this function
 * @return A pointer to the KDTree created
*/
KDNode * buildKDTree(Point ** points, int n, int depth) {
    /**
     *       The tree will contain all the points in the 
     *       its leaf nodes. Just beacause a point has been used
     *       to create another node (draw a line) that doesn't
     *       mean that it won't show in a leaf node. It can actually 
     *       be used to draw multiple lines at different depths, 
     *       if the circumstances demand so. 
     * 
     *       The lines don't identify with the points, but rather the points
     *       are used to help center the lines. The line could also 
     *       be drawn at a defferent position, that is still centered.
     *       The points just help to do the precedure faster.
     * 
     *       Also, the points will be stored in the leaves in an
     *       increasing order, not based only on either the x or y 
     *       coordinate, but rather in a manner relevant to the plane.
    */


    // make sure the Points array is valid and
    // base case for invalid amount of points
    if (!points || n <= 0) return NULL;


    // base case for recursion to end:
    // only one point left in the array
    // create leaf node and return it  
    if (n == 1) {
        KDNode * LeafNode = kdnode_init(points[0], 0, LEAF_NODE);
        return (LeafNode) ? LeafNode : NULL;
    }


    // sort the points in the current subset based on the depth
    qsort(points, n, sizeof(Point *), (depth % 2) ? point_compare_y : point_compare_x);


    int med = (int)ceil((n)/2.0);
   
    // reduce this by 1 because of the 0-based index
    med--;
        
    NodeType type = (!(depth % 2)) ? VERTICAL_LINE : HORIZONTAL_LINE;

    KDNode * v = kdnode_init(NULL, (depth % 2) ? points[med]->y : points[med]->x, type);
    
    // create the children
    
    v->left = buildKDTree(points, med + 1, depth + 1);

    v->right = buildKDTree(points + med + 1, (n - med - 1 == 0) ? 1 :  n - med - 1, depth + 1);

    return v;

}

/**
 * @brief Function search for points inside a given range
 * @note Used the List code from hw0 of this course.
 * @note Pass the list as a pointer to the function for recursive calls and do not create a new one with each call.
 * @param root The tree’s root
 * @param range The query range
 * @param region the region of the current node
 * @param l List to store the results
 * @return -
*/
void searchKDTree(KDNode * root, Range * range, Range * region, List l) {
    if (!l || !root) return;

    if (root->type == LEAF_NODE) {
        // check if the point is inside the range
        // and if yes, add it to the list
        if (point_in_range(root->point, range)) {
            AddFirst(l, root->point);
        }
        return;
    } else {
        // check if the region(lc(v)) is fully contained in the range
        
        Range * lc_region = (root->type == VERTICAL_LINE) ? intersect_square_on_x_left(region, root->line) : intersect_square_on_y_down(region, root->line);

        if (!lc_region) return;


        if (range_contains(range, lc_region)) {
            // use this helper function to report all the point in lc_region
            ReportSubtree(root->left, l);
        } else if (range_intersect(range, lc_region)) {
            // check if the point is inside the range
            // and if yes, add it to the list
            searchKDTree(root->left, range, lc_region, l);
        }


        Range * rc_region = (root->type == VERTICAL_LINE) ? intersect_square_on_x_right(region, root->line) : intersect_square_on_y_up(region, root->line);
        if (!rc_region) return;


        if (range_contains(range, rc_region)) {
            // use this helper function to report all the point in ρc_region
            ReportSubtree(root->right, l);
        } else if (range_intersect(range, rc_region)) {
            // check if the point is inside the range
            // and if yes, add it to the list
            searchKDTree(root->right, range, rc_region, l);
        }

        // free the regions
        free(lc_region);
        free(rc_region);
    }
}

/**
 * @brief Function to destroy a KDTree
 * @param root A pointer to the root of the Tree
 * @return -
*/
void destroyKDTree(KDNode * root) {
    if (root == NULL) {
        return;
    }
    
    // First free children recursively
    if (root->left != NULL) {
        destroyKDTree(root->left);
    }
    
    if (root->right != NULL) {
        destroyKDTree(root->right);
    }
    
    // Then free current node's data
    if (root->type == LEAF_NODE && root->point != NULL) {
        free(root->point);
    }
    
    // Finally free the node itself
    free(root);
}

#endif