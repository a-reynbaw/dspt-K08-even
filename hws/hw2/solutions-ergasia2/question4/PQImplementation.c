/** 
    @file PQImplementation.c
    @author Anastasia Marinakou | sdi2400120
    @details Course : Data Structures and Programing Techniques (Even)
    @brief Implementation of Priority Queue
*/

#ifndef PQIMPLEMENTATION_C
#define PQIMPLEMENTATION_C

#include <stdlib.h>
#include <stdio.h>
#include "PQInterface.h"

/**
    @brief initializes a priority queue and its fields
    @param maxN max Item capacity in the ItemArray
    @return PQPointer (pointer to a PQ struct)
*/
PQPointer QUEUEinit(int maxN) {
    PQPointer PQ = (PQPointer)malloc(sizeof(struct priority_queue));

    if (!PQ) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    // init the count as 0, no item has been added yet
    PQ->Count = 0;

    // create the ItemArray based on the number of elements (maxN)
    // given by the caller
    PQ->ItemArray = (Item *)malloc(sizeof(Item) * (maxN + 1));

    if (!PQ->ItemArray) {
        fprintf(stderr, "Unable to allocate memory\n");
        // free the pointer before exiting to avoid leaks
        free(PQ); 
        exit(1);
    }

    return PQ;
}

/**
    @brief checks if a PQ is empty
    @param PQ PQPointer to the PQ in question
    @return number indicating if the PQ is empty (1 == empty, 0 == not empty)
*/
int QUEUEempty(PQPointer PQ) {
    return (PQ->Count == 0);
}

/**
    @brief inserts a new item in the PQ
    @param PQ PQPointer to the PQ in question
    @param element item to be inserted
    @return none
*/
void QUEUEput(PQPointer PQ, Item element) {
    
    // increase the count of elements in the PQ
    (PQ->Count)++;

    // start at the newly added position (last leaf)
    int position = PQ->Count;


    // Perform up-heap (bubble-up) operation
    // Continue while we haven't reached the root and the 
    // element has higher priority than its parent
    while ( (position > 1) && (element < PQ->ItemArray[position/2]) ) {
        // copy parent down to current position
        PQ->ItemArray[position] = PQ->ItemArray[position/2];
        // move up to parent's position
        position = position/2;

    }

    // place the element at its current position
    PQ->ItemArray[position] = element;

    return;
    
}

/**
    @brief removes the Item with the highest priority from the PQ
    @param PQ PQPointer to a PQ
    @return the Item with the highest priority (top)
*/
Item QUEUEget(PQPointer PQ) {
    // remove the last item, which is the one with the largest priority
    return PQ->ItemArray[PQ->Count--];
}

/*------------------------| EXTRA FUNCTIONS FOR PRINTING AND FREEING |------------------------*/

/**
    @brief Prints a PQ
    @param PQ PQPointer to a PQ
    @return none
*/
void QUEUEprint(PQPointer PQ) {
    // print the PQ in iversed order, to show the Item with
    // the highest priority first
    int i;

    for (i = 1; i <= PQ->Count; i++) {
        printf("%d, ", PQ->ItemArray[i]);
    }

    printf("\n");
    
    return;

}

/**
    @brief Frees memory blocks allocated for a PQ
    @param PQ PQPointer to a PQ
    @return none
*/
void QUEUEfree(PQPointer PQ) {

    free(PQ->ItemArray);
    free(PQ);
    
    return;
}

#endif