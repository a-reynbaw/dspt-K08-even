/** 
    @file PQImplementation.h
    @author Anastasia Marinakou | sdi2400120
    @details Course : Data Structures and Programing Techniques (Even)
    @brief Interface for a Priority Queue impemented in "PQImplementation"
*/

#ifndef PQINTERFACE_H
#define PQINTERFACE_H

#include "PQTypes.h"

typedef struct priority_queue{
    int Count;
    Item *ItemArray;
} PriorityQueue;

typedef PriorityQueue *PQPointer;

PQPointer QUEUEinit(int maxN);
int QUEUEempty(PQPointer);
void QUEUEput(PQPointer, Item);
Item QUEUEget(PQPointer);

// added two more functions to make main and tests easier

void QUEUEprint(PQPointer);
void QUEUEfree(PQPointer);

#endif