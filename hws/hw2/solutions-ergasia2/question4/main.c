/* File:   main.c
   Author: Anastasia Marinakou | sdi2400120
   Course: Data Structures and Programing Techniques (Even)

   Brief: Main program/interface for user to use PQImplementation.c 
*/

#include <stdlib.h>
#include <stdio.h>
#include "PQInterface.h"
#include "PQTypes.h"

void menu (PQPointer PQ, int maxN) {
    int choice, num;

    // create a menu for the user
    do {
        // print options
        printf("------------------------------\n1. Insert\n2. Remove\n3. Exit\n-> ");

        // read the choice until it is an acceptable one
        do {
            scanf("%d", &choice);

            if (choice < 1 || choice > 3) {
                printf("Wrong input, please choose again.\n-> ");
            }

        } while (choice < 1 || choice > 3);

        if (choice == 1) {
            // Choose to insert an Item
            if (PQ->Count == maxN) {
                printf("!!! Maximuim capacity for this Priority Queue has been reached. Remove an item before inserting a new one. !!!\n");
                continue;
            }

            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\nGive number to insert:\n-> ");

            scanf("%d", &num);

            QUEUEput(PQ, num);

            printf("> Updated queue:\n");
            
            QUEUEprint(PQ);

        } else if (choice == 2) {
            // Choose to remove the Item with the highest priority
            if (PQ->Count == 0) {
                printf("!!! Priority Queue is empty. Insert items before removing. !!!\n");
                continue;
            }

            num = QUEUEget(PQ);

            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~\nRemoved Item: %d\n", num);

            printf("> Updated queue:\n");
            
            QUEUEprint(PQ);

        }

    } while ( choice != 3 );

    return;
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num>\n", argv[0]);
        return 1;
    }

    // number of max elements in the PQ, given from the user
    int maxN = atoi(argv[1]);

    if (maxN <= 0) {
        fprintf(stderr, "Invalid Priority Queue size. Terminating.\n");
        return 1;
    }

    // init the PQ
    PQPointer PQ = QUEUEinit(maxN);

    menu(PQ, maxN);
    
    QUEUEfree(PQ);

    return 0;
}