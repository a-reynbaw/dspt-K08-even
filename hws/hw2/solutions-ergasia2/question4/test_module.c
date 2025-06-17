/* File:   test_module.c
   Author: Anastasia Marinakou | sdi2400120
   Course: Data Structures and Programing Techniques (Even)

   Brief: test module using acutest library, to demonstrate functionality of PQImplementation.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "PQInterface.h"
#include "PQTypes.h"
#include "acutest/acutest.h"

// define the max size of PQs in this module
#define maxN 10


void test_QUEUEinit() {
    PQPointer PQ = QUEUEinit(maxN);

    // check if the PQPointer is not NULL, the PQ->Count = 0 
    // and PQ->ItemArray is not NULL
    TEST_CHECK(PQ && !PQ->Count && PQ->ItemArray);

    QUEUEfree(PQ);
}

void test_QUEUEempty() {
    PQPointer PQ = QUEUEinit(maxN);

    // x should be 1 since the PQ is empty
    int x = QUEUEempty(PQ);

    QUEUEput(PQ, 5);

    // and y should be 0, since "5" has been added to the PQ
    int y = QUEUEempty(PQ);

    TEST_CHECK(x && !y);

    QUEUEfree(PQ);
}

void test_QUEUEput() {
    PQPointer PQ = QUEUEinit(maxN);

    QUEUEput(PQ, 5);
    QUEUEput(PQ, 9);
    QUEUEput(PQ, 4);
    QUEUEput(PQ, 1);

    // check if the count is 4 and that when removing, the items are the expected ones
    // meaning that they were added in the corrent order
    TEST_CHECK( (PQ->Count == 4) && (QUEUEget(PQ) == 9) && (QUEUEget(PQ) == 5) && (QUEUEget(PQ) == 4) && (QUEUEget(PQ) == 1) );

    QUEUEfree(PQ);
}

void test_QUEUEget() {
    PQPointer PQ = QUEUEinit(maxN);

    QUEUEput(PQ, 5);
    QUEUEput(PQ, 9);

    // check if the items are removed in correct order and that the count is decreased accordingly
    TEST_CHECK( ((QUEUEget(PQ) == 9) && (PQ->Count == 1)) && ((QUEUEget(PQ) == 5) && (PQ->Count == 0)) );

    QUEUEfree(PQ);
}

TEST_LIST = {
    { "test_QUEUEinit", test_QUEUEinit  },
    { "test_QUEUEempty", test_QUEUEempty  },
    { "test_QUEUEput", test_QUEUEput  },
    { "test_QUEUEget", test_QUEUEget  },
    { NULL, NULL }
};