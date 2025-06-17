#ifndef TREEINTERFACE_H
#define TREEINTERFACE_H

#define ERROR -10000
#define EMPTY 10000

typedef int Item;
typedef int Key;

typedef struct t24 Tree24;

struct t24 {
    // tracks the amount of items stored in this node
    int Count;
    
    // pointer to a parent node
    Tree24 *parent;

    // NOTE: increased each of the arrays by one 
    // in order to deal easier with overflow during insertion
    
    // array storing up to 3 Items
    Item items[4];

    // array of pointer to child nodes (up to 4)
    Tree24 *children[5];

    // count of nodes in each subtree "i"
    int N[5];
};

// added this wrapper to ensure cosnistent access

void newline();

void visit(Item);

void init();
int count();
void insert(Item);
Item search(Key); 
void delete(Item);
Item find(int); // select was renamed as find because of confinct with the GNU C library 
void sort(void (*visit)(Item));

void destroy();


#endif