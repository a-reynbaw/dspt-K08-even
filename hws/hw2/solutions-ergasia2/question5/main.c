/**  
    @file main.c
    @author Anastasia Marinakou | sdi2400120
    @details Course: Data Structures and Programming Techniques (Even) - 2025
    @brief main function to demonstrate how Tree24Implementation.c works
*/

#ifndef QUESTION5_C
#define QUESTION5_C

#include <stdlib.h>
#include <stdio.h>
#include "Tree24Interface.h"

// use the global (2, 4) Tree from "Tree24Implementation.c"
extern Tree24 * T;

int main() {
    // create tree
    printf("\n*************\nCreating Tree...\n");

    init();

    printf("\nTree Created!\n*************\n\n");

    do {
        printf("========= MENU =========\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Find\n");
        printf("5. Sort\n");
        printf("6. Count\n");
        printf("7. Exit\n");
        printf("========================\n");
        
        
        int choice;
        do {
            printf("Enter your choice: ");
            scanf("%d", &choice);
            if (choice < 1 || choice > 7) {
                printf("Invalid choice. Please try again.\n");
            }
        } while (choice < 1 || choice > 7);

        switch (choice) {
            case 1: {
                int item;
                printf("Enter item to insert: ");
                scanf("%d", &item);
                insert(item);
                break;
            }
            case 2: {
                int item;
                printf("Enter item to delete: ");
                scanf("%d", &item);
                delete(item);
                break;
            }
            case 3: {
                int item;
                printf("Enter item to search: ");
                scanf("%d", &item);
                int result = search(item);
                if (result != ERROR) {
                    printf("%d is in the tree\n", result);
                } else {
                    printf("%d is not in the tree\n", item);
                }
                break;
            }
            case 4: {
                int k;
                printf("Enter k to find the k-th smallest item: ");
                scanf("%d", &k);
                int result = find(k);
                if (result != ERROR) {
                    printf("The %d-th smallest item is %d\n", k, result);
                } else {
                    printf("Error finding the %d-th smallest item\n", k);
                }
                break;
            }
            case 5:
                sort(visit);
                break;
            case 6: {
                int cnt = count();
                if (cnt != ERROR) {
                    printf("Total key count: %d\n", cnt);
                } else {
                    printf("Error counting keys\n");
                }
                break;
            }
            case 7:
                destroy();
                exit(0);
        }
    } while (1);
      

    return 0;
}

#endif