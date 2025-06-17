/**
 * @file RangeImplementation.c
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief TBD
*/

#ifndef RANGE_IMPLEMENTATION_C
#define RANGE_IMPLEMENTATION_C

// for memory allocation
#include <stdlib.h>
// for stdout and stderr use
#include <stdio.h>
// all implemented header files in this directory
#include "RangeInterface.h"
#include "PointInterface.h"

/**
 * @brief Function to initialize a new Range
 * @param xmin x-coordinate range lower bound
 * @param xmax x-coordinate range upper bound
 * @param ymin y-coordinate range lower bound
 * @param ymax y-coordinate range upper bound
 * @return pointer to the new Range
*/
Range * range_init(double xmin,double xmax,double ymin,double ymax) {
    Range * NewRange = (Range *)malloc(sizeof(struct range));

    if (!NewRange) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // set all fields inside NewRange to the 
    // ones provided by the caller
    NewRange->xmin = xmin;
    NewRange->xmax = xmax;
    NewRange->ymin = ymin;
    NewRange->ymax = ymax;

    return NewRange;
}

/**
 * @brief Function to check if a point p is
 * @param p Point to check if inside the range (square)
 * @param R range (square) to look if p is within it
 * @return 1: point is inside the range, 0: point is not inside the range
*/
int point_in_range(Point * p, Range * R) {
    // return the result of this statement, which 
    // set all the prerequisites for p to b inside R
    return ( (p->x >= R->xmin) && (p->x <= R->xmax) && (p->y >= R->ymin) && (p->y <= R->ymax) );
}

/**
 * @brief Function to check if two squares intersect
 * @param r1 first range (square)
 * @param r2 second range (square)
 * @return 1: if the two squares intersect, 0: if they don't intersect
*/
int range_intersect(Range * r1, Range * r2) {
    return !(r1->xmax < r2->xmin || r1->xmin > r2->xmax || r1->ymax < r2->ymin || r1->ymin > r2->ymax);
}



/*   For the following four functions, I switched the names so they would make more sense   */


/**
 * @brief Function to create a new range (square) based on the given one
 * @details it is usefull when trying to find the region of a child of a node (this one finds region(lc(v)) when the node is a vertical line)
 * @param square the square to be used as a base
 * @param x the x coordinate to be used for the new range
 * @return pointer to the new range
*/
Range * intersect_square_on_x_left(Range * square, double x) {
    // create a new range
    Range * NewRange = (Range *)malloc(sizeof(struct range));

    if (!NewRange) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // set the new range's values
    NewRange->xmin = square->xmin;
    NewRange->xmax = x;
    NewRange->ymin = square->ymin;
    NewRange->ymax = square->ymax;

    return NewRange;
}

/**
 * @brief Function to create a new range (square) based on the given one
 * @details it is usefull when trying to find the region of a child of a node (this one finds region(rc(v)) when the node is a vertical line)
 * @param square the square to be used as a base
 * @param x the x coordinate to be used for the new range
 * @return pointer to the new range
*/
Range * intersect_square_on_x_right(Range * square, double x) {
    // create a new range
    Range * NewRange = (Range *)malloc(sizeof(struct range));

    if (!NewRange) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // set the new range's values
    NewRange->xmin = x;
    NewRange->xmax = square->xmax;
    NewRange->ymin = square->ymin;
    NewRange->ymax = square->ymax;

    return NewRange;
}

/**
 * @brief Function to create a new range (square) based on the given one
 * @details it is usefull when trying to find the region of a child of a node (this one finds region(lc(v)) when the node is a horizontal line)
 * @param square the square to be used as a base
 * @param y the y coordinate to be used for the new range
 * @return pointer to the new range
*/
Range * intersect_square_on_y_up(Range * square, double y) {
    // create a new range
    Range * NewRange = (Range *)malloc(sizeof(struct range));

    if (!NewRange) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // set the new range's values
    NewRange->xmin = square->xmin;
    NewRange->xmax = square->xmax;
    NewRange->ymin = y;
    NewRange->ymax = square->ymax;

    return NewRange;
}

/**
 * @brief Function to create a new range (square) based on the given one
 * @details it is usefull when trying to find the region of a child of a node (this one finds region(rc(v)) when the node is a horizontal line)
 * @param square the square to be used as a base
 * @param y the y coordinate to be used for the new range
 * @return pointer to the new range
*/
Range * intersect_square_on_y_down(Range * square, double y) {
    // create a new range
    Range * NewRange = (Range *)malloc(sizeof(struct range));

    if (!NewRange) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // set the new range's values
    NewRange->xmin = square->xmin;
    NewRange->xmax = square->xmax;
    NewRange->ymin = square->ymin;
    NewRange->ymax = y;

    return NewRange;
}

/**
 * @brief Function to check if square 'outer' completely contains square 'inner'
 * @param outer the 'outer' square
 * @param inner the 'inner' square
 * @return 1: 'outer' completely cointains 'inner', 0: 'outer' doesn't completely cointains 'inner'
*/
int range_contains(Range * outer, Range * inner) {
    // return the result of this statement, which 
    // set all the prerequisites for 'outer' to 
    // completely contain 'inner'
    return ( (inner->xmin > outer->xmin) && (inner->xmax <= outer->xmax) && (inner->ymin > outer->ymin) && (inner->ymax <= outer->ymax) );
}

/**
 * @brief Function to print the range
 * @param r the range to be printed
 * @return -
*/
void print_range(Range * r) {
    if (!r) return;

    printf(" lower left: (%lf, %lf)\n", r->xmin, r->ymin);
    printf(" upper left: (%lf, %lf)\n", r->xmin, r->ymax);
    printf(" upper right: (%lf, %lf)\n", r->xmax, r->ymax);
    printf(" lower right: (%lf, %lf)\n", r->xmax, r->ymin);

    return;
}
#endif