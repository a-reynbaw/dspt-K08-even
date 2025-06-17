/**
 * @file PointInterface.h
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief Interface for the Point structure used in main.c, kdTreeImplementation.c and other implementation files
*/

#ifndef POINT_INTERFACE_H
#define POINT_INTERFACE_H

typedef struct point{
    double x;
    double y;
} Point;
   
//Point functions - Helper functions you will find useful on your implementation

Point * point_init(double, double);
// Function type declaration - no need to implement
// anything for this - simply include it in your code
   
typedef int (* PointComparator)(const void * a,const void * b);

//Comparator functions to be used with qsort()
//Function to compare a point on the x/y-coordinate
int point_compare_x(const void *a,const void *b);

int point_compare_y(const void *a,const void *b);


#endif