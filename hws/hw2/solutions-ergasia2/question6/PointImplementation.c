/**
 * @file PointImplementation.c
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief 
*/

#ifndef POINT_IMPLEMENTATION_C
#define POINT_IMPLEMENTATION_C

// for memory allocation
#include <stdlib.h>
// for stderr use
#include <stdio.h>

#include "PointInterface.h"

Point * point_init(double x, double y) {
    Point * NewPoint = (Point *)malloc(sizeof(struct point));
    if (!NewPoint) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    NewPoint->x = x;
    NewPoint->y = y;

    return NewPoint;
}


// although said not to implement, had to to check
// if other functions work correctly

int point_compare_x(const void *a,const void *b) {
    // cast to Point** then dereference to get Point*
    Point *p1 = *(Point **)a;  
    Point *p2 = *(Point **)b;
    
    if (p1->x < p2->x) return -1;
    // add this extra statement in case the
    // x coordinates are equal, so compare y coordinates
    
    if (p1->x == p2->x) {
        if (p1->y < p2->y) return -1;
        if (p1->y > p2->y) return 1;
        return 0;
    }

    if (p1->x > p2->x) return 1;
    return 0;
}

int point_compare_y(const void *a,const void *b) {
    Point *p1 = *(Point **)a;
    Point *p2 = *(Point **)b;
    
    // add this extra statement in case the
    // y coordinates are equal, so compare x coordinates
    if (p1->y < p2->y) return -1;
    if (p1->y == p2->y) {
        if (p1->x < p2->x) return -1;
        if (p1->x > p2->x) return 1;
        return 0;
    }

    if (p1->y > p2->y) return 1;
    return 0;
}


#endif