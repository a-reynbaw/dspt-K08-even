/**
 * @file RangeInterface.h
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief Interface for Squares (Ranges) used in kdTreeImplementation.c
*/

#ifndef RANGE_INTERFACE_H
#define RANGE_INTERFACE_H

#include "PointInterface.h"

// default plane limitations, change these if you want
// to import larger/smaller values
#define PLANE_X_MIN 0.000000
#define PLANE_X_MAX 15.000000
#define PLANE_Y_MIN 0.000000
#define PLANE_Y_MAX 15.000000

// Using only four variables we can easily
// represent a square of the form:
// [(xmin,ymin),(xmax,ymin),(xmin,ymax),(xmax,ymax)]
typedef struct range {
    double xmin, xmax;
    double ymin, ymax;
} Range;


Range * range_init(double, double, double, double);

int point_in_range(Point *, Range *);

int range_intersect(Range *, Range *);

// Four symmetrical functions. Very useful for
// calculating the region of a child of a node
// i.e region(lc(v)) or region(rc(v))

Range * intersect_square_on_x_left(Range *, double);
Range * intersect_square_on_x_right(Range *, double);
Range * intersect_square_on_y_up(Range *, double);
Range * intersect_square_on_y_down(Range *, double);

int range_contains(Range *, Range *);

void print_range(Range *);

#endif   