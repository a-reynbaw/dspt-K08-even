/**
 * @file main.c
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief demonstration of kdTree functionality
*/
#ifndef MAIN_C
#define MAIN_C

// for memory allocation
#include <stdlib.h>
// for stdin, stdout and stderr use
#include <stdio.h>
// all implemented header files in this directory
#include "kdTreeInterface.h"
#include "PointInterface.h"
#include "RangeInterface.h"
#include "ListInterface.h"

int main () {
    int num;
    /* ----------------------- ask for amount points ----------------------- */ 
    printf("\n>>> GIVE NUMBER OF POINTS:\n>>> ");
    scanf("%d", &num);

    if (num <= 0) {
        fprintf(stderr, "\n>>> INVALID AMOUNT OF POINTS\n");
        return 1;
    }

    Point ** points;
    points = (Point **)malloc(num * sizeof(Point *));

    if ( !points) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return 1;
    }

    
    /* ----------------------- ask for the points ----------------------- */ 

    double x, y;
    
    for (int i = 0; i < num; i++) {

        printf("\n>>> GIVE COORDINATES:\n");

        do {
            printf(">>> (x) ");
            scanf("%lf", &x);
            if (x < PLANE_X_MIN || x > PLANE_X_MAX) fprintf(stderr, "\n>>> INVALID X COORDINATE. INSERT AGAIN\n");
        } while (x < PLANE_X_MIN || x > PLANE_X_MAX);
            
        do {
            printf(">>> (y) ");
            scanf("%lf", &y);
            if (y < PLANE_Y_MIN || y > PLANE_Y_MAX) fprintf(stderr, "\n>>> INVALID Y COORDINATE. INSERT AGAIN\n");
        } while (y < PLANE_Y_MIN || y > PLANE_Y_MAX);
        
        points[i] = point_init(x, y);
    }

    /* ----------------------- create and build the tree ----------------------- */ 

    printf("\n>>> BUILDING KD TREE...\n");

    // create the tree by giving the points, a starting and an ending 
    // index, and the starting depth, which should always be 0
    KDNode * root = buildKDTree(points, num, 0);

    if (!root) return 1;

    printf("\n");

    printVisualTree(root, 0, "root");

    /* ----------------------- ask for the range query ----------------------- */ 
    
    double xmin, xmax, ymin, ymax;
    printf("\n>>> GIVE RANGE QUERY COORDINATES:\n");

    do {
        printf(">>> (xmin) ");
        scanf("%lf", &xmin);
        if (xmin < PLANE_X_MIN || xmin > PLANE_X_MAX) fprintf(stderr, "\n>>> INVALID X-MIN COORDINATE. INSERT AGAIN\n");
    } while (xmin < PLANE_X_MIN || xmin > PLANE_X_MAX);

    do {
        printf(">>> (xmax) ");
        scanf("%lf", &xmax);
        if (xmax < PLANE_X_MIN || xmax > PLANE_X_MAX) fprintf(stderr, "\n>>> INVALID X-MAX COORDINATE. INSERT AGAIN\n");
    } while (xmax < PLANE_X_MIN || xmax > PLANE_X_MAX);

    do {
        printf(">>> (ymin) ");
        scanf("%lf", &ymin);
        if (ymin < PLANE_Y_MIN || ymin > PLANE_Y_MAX) fprintf(stderr, "\n>>> INVALID Y-MIN COORDINATE. INSERT AGAIN\n");
    } while (ymin < PLANE_Y_MIN || ymin > PLANE_Y_MAX);

    do {
        printf(">>> (ymax) ");
        scanf("%lf", &ymax);
        if (ymax < PLANE_Y_MIN || ymax > PLANE_Y_MAX) fprintf(stderr, "\n>>> INVALID Y-MAX COORDINATE. INSERT AGAIN\n");
    } while (ymax < PLANE_Y_MIN || ymax > PLANE_Y_MAX);
    
    // create the range
    Range * range_query = range_init(xmin, xmax, ymin, ymax);
    if (!range_query) return 1;

    // these values have been defines in RangeInterface.h
    // where 0 <= x, y <= 15. If you want to change the values
    // of the plane, change them in the header file
    // and recompile
    Range * plane = range_init(PLANE_X_MIN, PLANE_X_MAX, PLANE_Y_MIN, PLANE_Y_MAX);
    if( !plane) return 1;

    // create the list for the points inside the range query
    List l = Create();

    if (!l) return 1;

    printf("\n>>> SEARCHING FOR POINTS INSIDE THE RANGE QUERY...\n");

    searchKDTree(root, range_query, plane, l);

    printf("\n");

    Print(l);


    /* ----------------------- free all memory allocated blocks ----------------------- */ 

    FreeList(l);

    free(plane);
    free(range_query);

    destroyKDTree(root);

    // free the memory allocated for the points
    for (int i = num - 1; i >= 0; i--) {
        free(points[i]);
    }

    free(points);

    return 0;
}

#endif