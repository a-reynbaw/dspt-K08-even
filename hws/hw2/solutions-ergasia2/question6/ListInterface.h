/**
 * @file ListInterface.h
 * @author Anastasia Marinakou | sdi2400120
 * @details Course: Data Structures and Programing Techniques (Even)
 * @brief Linked List Data Structure Interface
*/

#ifndef LIST_INTERFACE_H
#define LIST_INTERFACE_H

#include "PointInterface.h"

typedef struct list_tag * List;

List Create();

void AddFirst(List, Point *);

void FreeList(List);

void Print(List);

#endif