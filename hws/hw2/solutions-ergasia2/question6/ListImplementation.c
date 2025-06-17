/**
 * @file ListImplementation.c
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief Linked List Data Structure Implementation
*/

#ifndef LIST_IMPLEMENTATION_C
#define LIST_IMPLEMENTATION_C

// for memory allocation
#include <stdlib.h>
// for stdout and stderr use
#include <stdio.h>
// implemented header files in this directory
#include "ListInterface.h"
#include "PointInterface.h"

struct listnode {
    Point * value;
    
    struct listnode * next;
};


// Define the list tag structure that the client will use as a handle
struct list_tag {
    struct listnode * head;
};

/**
 * @brief Function to create a new list
 * @return pointer to the new list
*/
List Create() {
    // allocate memory for initial node
    List l = (List)malloc(sizeof(struct listnode));

    // check if allocation was successful. if not exit with code 1.
    if (l == NULL) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    // initiate list members
    l->head = NULL;

    return l;
}

/**
 * @brief Function to add a new point at the beginning of the list
 * @param l The list to add the point to
 * @param p The point to be added
 * @return -
*/
void AddFirst(List l, Point * p) {
    if (l == NULL) return;

    // allocate memory for the new node
    struct listnode * newNode = (struct listnode *)malloc(sizeof(struct listnode));

    // and check if it was successful
    if (newNode == NULL) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    // the point already exists in memory and 
    // the list just nedd to have reference to it
    // no need to create a new one point
    newNode->value = point_init(p->x, p->y);
    if (!newNode->value) {
        free(newNode);
        return;
    }
    
    newNode->next = l->head;
    
    l->head = newNode;

    return;
}

/**
 * @brief Function to free the list
 * @param l The list to be freed
 * @return -
*/
void FreeList(List l) {
    if (l == NULL) return;

    struct listnode * current = l->head;
    struct listnode * next;

    while(current) {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }

    // Free the list handle itself
    free(l);
    
    return;
}

/**
 * @brief Function to print the list
 * @param l The list to be printed
 * @return -
*/
void Print(List l) {
    if (l == NULL) {
        printf("NULL (Invalid list)\n");
        return;
    }

    struct listnode * current = l->head;

    while (current != NULL) {
        if (current->next != NULL) {
            printf("(%lf, %lf) <-> ", current->value->x, current->value->y);
        } else {
            printf("(%lf, %lf) -> NULL\n", current->value->x, current->value->y);
        }
        current = current->next;
    }

    if (l->head == NULL) {
        printf("NULL (Empty list)\n");
    }

    return;
}

#endif