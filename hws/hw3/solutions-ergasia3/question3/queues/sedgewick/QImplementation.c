/* This code is from Chapter 4 of the book "Algorithms in C" by Robert Sedgewick. */

#include <stdlib.h>
#include "Item.h"
#include "QUEUE.h"

typedef struct QUEUEnode* link;
struct QUEUEnode { Item item; link next; };
struct queue { link head; link tail; };

link NEW(Item item, link next)
  { link x = malloc(sizeof *x);
    x->item = item; 
    x->next = next;
    return x;
  }

Queue QUEUEinit()
  { Queue q = malloc(sizeof(struct queue));
    q->head = NULL; 
    q->tail = NULL;
    return q;
  }

int QUEUEempty(Queue q)
  { return q->head == NULL; }
  
void QUEUEput(Queue q, Item item)
  {
    if (q->head == NULL)
      { q->tail = NEW(item, q->head);
        q->head = q->tail; return; 
      }
    q->tail->next = NEW(item, q->tail->next);
    q->tail = q->tail->next;
  }
  
Item QUEUEget(Queue q)
  { Item item = q->head->item;
    link t = q->head->next;
    free(q->head); 
    q->head = t;
    return item;
  }

  void QUEUEdump(Queue q) {
    // Traverse the queue and free each node
    while (q->head != NULL) {
        link temp = q->head;  // Save the current head
        q->head = q->head->next;  // Move to the next node
        free(temp);  // Free the current node
    }
    // Free the queue structure itself
    free(q);
}