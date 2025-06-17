/* This code is from Chapter 4 of the book "Algorithms in C" by Robert Sedgewick. */
#include "Item.h"

typedef struct queue * Queue;
void QUEUEdump(Queue);
Queue QUEUEinit();
int QUEUEempty(Queue);
void QUEUEput(Queue, Item);
Item QUEUEget(Queue);
