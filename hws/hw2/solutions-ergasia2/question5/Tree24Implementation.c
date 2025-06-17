/**  
    @file Tree24Implementation.c
    @author Anastasia Marinakou | sdi2400120
    @details Course: Data Structures and Programming Techniques (Even) - 2025
    @brief Implementation of functions for a (2, 4) Search Tree
*/

#ifndef TREE24IMPLEMENTATION_C
#define TREE24IMPLEMENTATION_C

#include <stdlib.h>
#include <stdio.h>
#include "Tree24Interface.h"


// set the tree as a global variable
Tree24 * T;


void newline() {
    printf("\n");
}


/**
    @brief helper function to count the number of keys in a (2, 4) Tree
    @param node the node to count keys in
    @return the number of keys in the tree
*/
int count_recursive(Tree24 * node) {
    if (node == NULL) return 0;

    int count = node->Count;

    for (int i = 0; i <= node->Count; i++) {
        count += count_recursive(node->children[i]);
    }

    return count;
}


/**
    @brief helper function to create new nodes for the tree
    @return pointer to node 
*/
Tree24 * create_node() {
    Tree24 * node = (Tree24 *)malloc(sizeof(struct t24));

    if (node == NULL) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // init all fields
    node->Count = 0;
    node->parent = NULL;

    for (int i = 0; i < 4; i++) node->items[i] = EMPTY;

    for (int i = 0; i < 5; i++) {
        node->children[i] = NULL;
        node->N[i] = 0;
    }

    return node;
}

/**
    @brief helper function that recursively frees nodes in a (2, 4) Tree
    @param node the node to free along with its subtree
    @return -
*/
void destroyNode(Tree24 * node) {
    if (node == NULL) return;
    
    // First recursively free all children
    for (int i = 0; i <= node->Count; i++) {
        if (node->children[i] != NULL) {
            destroyNode(node->children[i]);
        }
    }
    
    // After all children are freed, free this node
    free(node);
}


/**
    @brief helper function to print tree nodes with proper indentation
    @param node current node to print
    @param visit function to print item values
    @param level current depth level for indentation
    @param path path string showing the position in the tree
    @return -
*/
void print_tree_helper(Tree24 * node, void (*visit)(Item), int level, char* path) {
    if (node == NULL) return;
    
    // Print indentation and path
    printf("%*s[%s] ", level*4, "", path);
    
    // Print node content
    printf("Node(%d keys): ", node->Count);
    for (int i = 0; i < node->Count; i++) {
        visit(node->items[i]);
    }
    printf("\n");
    
    // Print children
    char childPath[100];
    for (int i = 0; i <= node->Count; i++) {
        sprintf(childPath, "%s.%d", path, i);
        Tree24* savedT = T;
        T = node->children[i];
        print_tree_helper(node->children[i], visit, level + 1, childPath);
        T = savedT;
    }
}

/**
    @brief helper function to print tree keys, while traversing the nodes in-order
    @param node current node to print
    @return -
*/
void in_order(Tree24 * node) {
    if (node == NULL) return;
    
    // Check if leaf
    int isLeaf = 1;
    for (int i = 0; i <= node->Count; i++) {
        if (node->children[i] != NULL) {
            isLeaf = 0;
            break;
        }
    }
    
    if (isLeaf) {
        // For leaf nodes, just visit all items
        for (int i = 0; i < node->Count; i++) {
            visit(node->items[i]);
        }
    } else {
        // For internal nodes, visit in order
        for (int i = 0; i < node->Count; i++) {
            T = node->children[i];
            in_order(T);
            T = node;
            visit(node->items[i]);
        }
        
        // Visit rightmost child
        T = node->children[node->Count];
        in_order(T);
        T = node;
    }
}

/**
    @brief function passed on to other functions to print the keys in a node.
    @details using the function provided if lab-5
    @param i Item to print
    @return none
*/
void visit(Item i) {
    printf("%d ", i);
}


/////////////////////////////////////////////////////////////////////////////////////////////


/** 
    @brief init the (2, 4) Tree, which has been declared as global
    @param -
    @return -
*/
void init() {
    T = (Tree24 *)malloc(sizeof(struct t24));

    if (!T) {
        fprintf(stderr, "Unable to allocate memory.\n");
        exit(1);
    }

    T->Count = 0;
    T->parent = NULL;

    for (int i = 0; i < 4; i++) T->items[i] = EMPTY;

    for (int i = 0; i < 5; i++) {
        T->children[i] = NULL;
        T->N[i] = 0;
    }

    return;
}


/** 
    @brief count how many keys are in the (2, 4) Tree in total
    @param -
    @return the count of all the keys in the tree
*/
int count() {
    if (T == NULL) {
        fprintf(stderr, "Tree is not initiallized.\n");
        return ERROR;
    } else if (T->Count == 0) {
        fprintf(stderr, "Tree is empty.\n");
        return ERROR;
    }

    // use the recursive helper function to count the keys
    return count_recursive(T);
}


/**
    @brief insert a new Item in a (2, 4) Tree
    @param x the new Item to be inserted
    @return none
*/
void insert(Item x) {
    if (T == NULL) {
        fprintf(stderr, "Tree is not initiallized.\n");
        return;
    } 

    // save the root for easy recover
    Tree24 * OriginalTree = T;


    // start by finding the right position to insert x
    // if x is found in the Tree during this process,
    // return since no duplicates are allowed.
    while (T->children[0] != NULL) {
        int moving_flag = 0;
        
        for (int i = 0; i < T->Count; i++) {
            
            if (x == T->items[i]) {
                fprintf(stderr, "Item has already been inserted in the Tree.\n");
                T = OriginalTree;
                return;
            } else if (x < T->items[i]) {
                T = T->children[i];
                moving_flag = 1;
                break;
            }

        }
        
        // if the right child hasn't been found
        // (meaning that x > than the last key)
        // search the right-most child
        if (!moving_flag) T = T->children[T->Count];

    }


    // if the while loop has ended it means that we have
    // reached a leaf node (T->children[0] == NULL)
    // so now we need to search if x is in this node
    // otherwise, insert x here.

    int position;

    for (int i = 0; i < T->Count; i++) {
        if (x == T->items[i]) {
            fprintf(stderr, "Item has already been inserted in the Tree.\n");
            T = OriginalTree;
            return;
        } else if (x < T->items[i]) {
            // if x is less than item[i], then the right position to
            // insert it has passed, so save position = i-1 and break
            // (so that the position doesn't change in further iterations)
            position = i;
            break;
        }
    }


    // other cases
    if (T->Count == 0) {
        // special case: x is the first element to be inserted in the tree
         position = 0;
    } else if (x > T->items[T->Count - 1]) {
        // otherwise, x is the largest element in this node and must be inserted last
        position = T->Count;
    }


    // shift items to make room for the new key
    for (int i = T->Count; i > position; i--) T->items[i] = T->items[i - 1];
    T->items[position] = x;
    T->Count++;


    // check for overflow
    while (T->Count > 3) {
        
        // create new node
        Tree24 * NewNode = create_node();

        if (NewNode == NULL) {
            T = OriginalTree;
            return;
        }

        // also save the current node and move T up to the parent
        Tree24 * CurrentNode = T;

        // move the fourth key and the last two children to the new node
        NewNode->items[0] = CurrentNode->items[3];
        NewNode->children[0] = CurrentNode->children[3];
        NewNode->children[1] = CurrentNode->children[4];

        // update the parents
        if (NewNode->children[0]) {
            NewNode->children[0]->parent = NewNode;
            NewNode->children[1]->parent = NewNode;
        }

        // erase the data from this part of the array
        CurrentNode->children[3] = NULL;
        CurrentNode->children[4] = NULL;

        // update the key counts for each node
        NewNode->Count++;
        CurrentNode->Count--;
        // and the N array as well 
        NewNode->N[0] = CurrentNode->N[3];
        NewNode->N[1] = CurrentNode->N[4];

        CurrentNode->N[3] = 0;
        CurrentNode->N[4] = 0;

        // check if T is currenty the root
        if (CurrentNode == OriginalTree) {
            Tree24 * NewRoot = create_node();

            // no need to recover here - we are already at the root
            // and can return immediately
            if (NewRoot == NULL) return;

            // update the recovering address
            OriginalTree = NewRoot;

            // init all the NewRoot Data
            // contains only the third key from CurrentNode
            NewRoot->Count = 1;

            NewRoot->items[0] = CurrentNode->items[2];

            NewRoot->parent = NULL;
            
            NewRoot->children[0] = CurrentNode;
            NewRoot->children[1] = NewNode;
            NewRoot->children[2] = NULL;
            NewRoot->children[3] = NULL;

            NewNode->parent = NewRoot;

            // update the current node data
            CurrentNode->parent = NewRoot;
            
            CurrentNode->Count--;

            // init the N array for NewRoot
            // for the subtree rooted at CurrentNode, N will be equal to the sum
            // of N for each of its children + the 2 keys it contains now (after spliting)
            NewRoot->N[0] = CurrentNode->N[0] + CurrentNode->N[1] + CurrentNode->N[2] + 2;

            // for the subtree rooted at NewNode, N will be equal to the sum
            // of N for each of its children + the 1 key it contains now (after spliting)
            NewRoot->N[1] = NewNode->N[0] + NewNode->N[1] + 1;

            NewRoot->N[2] = 0;
            NewRoot->N[3] = 0;

            T = OriginalTree;
            
    
        } else {
            T = T->parent;

            // also add the parent of the new node to be T
            NewNode->parent = T;

            // now add the third key to the parent node
            for (int i = T->Count; i >= 0; i--) {
                
                T->items[i] = T->items[i - 1];
                if (CurrentNode->items[2] > T->items[i - 1]) {
                    T->items[i] = CurrentNode->items[2];
                    break;
                }
            }

            // update counts for T and Current Node
            T->Count++;
            CurrentNode->Count--;

            // contains CurrentNode's position in T's children
            int position;

            // also add NewNode as a child for T
            for (int i = T->Count - 1; i >= 0; i--) {
                
                if (T->children[i] == CurrentNode) {
                    position = i;
                    break;
                }
                
                // if the right position to add the address of NewNode
                // hasn't been found, shift the other children to make room
                // for the new one
                T->children[i + 1] = T->children[i];
            }

            // NewNode should be to the right of CurrentNode
            T->children[position + 1] = NewNode;

            
            // for the subtree rooted at CurrentNode, N will be equal to the sum
            // of N for each of its children + the 2 keys it contains now (after spliting)
            T->N[position] = CurrentNode->N[0] + CurrentNode->N[1] + CurrentNode->N[2] + 2;
            // for the subtree rooted at NewNode, N will be equal to the sum
            // of N for each of its children + the 1 key it contains now (after spliting)
            T->N[position + 1] = NewNode->N[0] + NewNode->N[1] + 1;
        }

        // this spliting operation repeats for as many times as it's needed to avoid overflow
    }

    // restore tree to its original state before returning
    T = OriginalTree;
    
    printf("Inserted %d\n", x);

    return;

}


/**  
    @brief search if a key is inside a (2, 4) Tree
    @param k key to search for
    @return the key itself if it exists in the Tree, otherwise NULL
*/
Item search(Key x) {
    if (T == NULL) {
        fprintf(stderr, "Tree is not initiallized.\n");
        return ERROR;
    } else if (T->Count == 0) {
        fprintf(stderr, "Tree is empty.\n");
        return ERROR;
    }

    Tree24 * OriginalTree = T;

    // find which child to follow
    // use this to determine if the item has been found or not
    int position = -1;

    while ((T->children[0] != NULL) && (position == -1)) {
        // use this to determine if a correct path has been chosen
        int moving_flag = 0;
        for (int i = 0; i < T->Count; i++) {
            if (x == T->items[i]) {
                T = OriginalTree;
                return x;
            } else if (x < T->items[i]) {
                T = T->children[i];
                moving_flag = 1;
                break;
            }
        }

        if (!moving_flag) T = T->children[T->Count];

    }

    // if this point has been reached, search the current (leaf) node
    
    for (int i = 0; i < T->Count; i++)  {
        if (x == T->items[i])  {
            T = OriginalTree;
            return x;
        }
    }
    
        
    // at this point, the Item isn't in the Tree, so 
    // restore and return error
    T = OriginalTree;
    return ERROR;

}


/**  
    @brief remove an Item from a (2, 4) Tree
    @param x the Item to remove from the Tree
    @return the key itself if it exists in the Tree, otherwise NULL
*/
void delete(Item x) {
    if (T == NULL) {
        fprintf(stderr, "Tree is not initiallized.\n");
        return;
    } else if (T->Count == 0) {
        fprintf(stderr, "Tree is empty.\n");
        return;
    }

    // save the root for easy restoration
    Tree24 * OriginalTree = T;

    // to save the Item's postion in the current node
    int position = -1;

    // search for x in the tree as long as a leaf node 
    // hasn't been reached and the item hasn't been found
    while ((T->children[0] != NULL) && (position == -1)) {
        
        int moving_flag = 0;
        for (int i = 0; i < T->Count; i++) {
            if (x == T->items[i]) {
                
                position = i;
                moving_flag = 1;
                break;
            } else if (x < T->items[i]) {
                T = T->children[i];
                moving_flag = 1;
                break;
            }
        }

        if (!moving_flag) T = T->children[T->Count];

    }

    // finally search in this node, which is a leaf
    if (position == -1)
        for (int i = 0; i < T->Count; i++) 
            if (x == T->items[i]) 
                position = i;
        
    
    // if position is still -1, then the item is not in the tree and cannot be removed
    if (position == -1) {
        fprintf(stderr, "Item is not in the Tree and cannot be deleted.\n");
        // restore tree to its original state berfore returning
        T = OriginalTree;
        return;
    }

    
    // determine if the node containing x is a leaf node or not
    // since each case follows a different process

    // use this to now if a switch has been done
    int flag = 0;

    if (T->children[0] != NULL) {
        
        // examine the possibility of T having internal children first
        Tree24 * CurrentNode = T;

        // find a good candidate to replace
        T = T->children[position];
        
        // move to the last child each time to find the right-most value
        while (T->children[0] != NULL) T = T->children[T->Count];

        // replace the deleting value with the highest one in T
        
        CurrentNode->items[position] = T->items[--T->Count];
        
        flag = 1;
    }

    // now that the switch has been done, check for underflow

    // if this node v has only external node children means it's a leaf node

    // only do this if a switch hasn't been done
    if (!flag) {
        // at first, we just remove x and shift items
        T->Count--;
        for (int i = position; i < T->Count; i++) T->items[i] = T->items[i + 1];
        // no need to change anything about children since this is a leaf
    }

    // check for underflow
    while (T->Count == 0) {
            
        Tree24 * CurrentNode = T;
            
        T = CurrentNode->parent;
            
        // if the root has been reached, delete it
        if (CurrentNode == OriginalTree) {
            T = CurrentNode->children[0];
            if (T) T->parent = NULL;
            free(OriginalTree);
            return;
        }

        // find CurrentNode's position in T's children
        // recycle "position" variable, no longer needed for its
        // original purpose.
        for (int i = 0; i <= T->Count; i++) 
            if (CurrentNode == T->children[i])
                position = i;

            
        if (position > 0) {
            //check if the left sibling of CurrentNode is a 3-node or a 4-node
            if (T->children[position - 1]->Count >= 2) {
                    
                // the left sibling of CurrentNode has two or more items
                // so a transfer (or rotation) can be performed
                Tree24 * TransferingNode = T->children[position - 1];
                    
                //save the parent key to move it to current node
                int transfering_key = T->items[position - 1];
                    
                // take the right-most key from TransferingNode and move it to the parent
                T->items[position - 1] = TransferingNode->items[TransferingNode->Count - 1];

                // finally add the parent key to the new node
                CurrentNode->items[0] = transfering_key;

                // no need to edit the children since a sibling of CurrentNode cannot have 
                // internal child nodes, due to the special properties of the 2-3-4 Trees

                // update the counts
                CurrentNode->Count++;
                TransferingNode->Count--;
            } else {
                // if T->children[position - 1]->Count isn't equal or greater than 2, it must be 1
                // in this case we perform a fusion operation
                Tree24 * FusionNode = T->children[position - 1];

                // fusion node is to the left of CurrentNode
                // so it's easier to keep the FusionNode and free CurrentNode after finishing the process
                // first, move the appropriate key from T to FusionNode
                    
                FusionNode->items[FusionNode->Count++] = T->items[position - 1];
                T->Count--;

                // don't forget to copy the children
                FusionNode->children[FusionNode->Count] = CurrentNode->children[0];

                // shift items in T
                for (int i = position - 1; i < T->Count; i++) T->items[i] = T->items[i + 1];


                // update the children
                for (int i = position; i <= T->Count; i++) T->children[i] = T->children[i + 1];
                T->children[T->Count + 1] = NULL;

                // now free the CurrentNode
                free(CurrentNode);
            }
                
        } else if (position <= T->Count - 1) {
            if (T->children[position + 1]->Count >= 2) {

                Tree24 * TransferingNode = T->children[position + 1];

                int transfering_key = T->items[position];

                // take the first key from TransferingNode and shift the items
                T->items[position] = TransferingNode->items[0];
                TransferingNode->Count--;
                for (int i = 0; i < TransferingNode->Count; i++) TransferingNode->items[i] = TransferingNode->items[i+1];

                CurrentNode->items[0] = transfering_key;

                CurrentNode->Count++;
            } else {
                // if T->children[position - 1]->Count isn't equal or greater than 2, it must be 1
                // in this case we perform a fusion operation
                Tree24 * FusionNode = T->children[position + 1];

                // fusion node is to the right of CurrentNode
                // so it's easier to keep the CurrentNode and free FusionNode after finishing the process
                // first, move the appropriate key from T to CurrentNode
                
                CurrentNode->items[0] = T->items[position];
                CurrentNode->Count++;
                    
                CurrentNode->items[1] = FusionNode->items[0];
                CurrentNode->Count++;

                    
                T->Count--;

                // shift items in T
                for (int i = position; i < T->Count; i++) T->items[i] = T->items[i + 1];
                // shift children in T
                for (int i = position + 1; i <= T->Count; i++) T->children[i] = T->children[i + 1];

                T->children[T->Count + 1] = NULL;
                // now free the CurrentNode
                free(FusionNode);
            }
        }
        
    }
    T = OriginalTree;
    
    printf("Deleted %d\n", x);

    return;
    
}


/**  
    @brief find the x-th smallest element in the (2, 4) Tree
    @param x the wanted Item's rank based on how small it is
    @return the x-th smallest Item in the Tree
*/
Item find(int x) {
    if (T == NULL) {
        fprintf(stderr, "Tree is not initiallized.\n");
        return ERROR;
    } else if (T->Count == 0) {
        fprintf(stderr, "Tree is empty.\n");
        return ERROR;
    }

    // handle invalid input : x out of range
    if (x <= 0) return ERROR;
    
    // total elements check
    if (x > count()) return ERROR;

    Tree24 * OriginalTree = T;
    
    Tree24 * current = T;
    
    // Iterate until we find the x-th element
    while (current != NULL) {
        int pos = 0;
        int cumulative_count = 0;
        
        // Check each subtree and item until we find where x falls
        while (pos <= current->Count) {
            // Add count of elements in this subtree
            
            int subtree_size = count_recursive(current->children[pos]);
            
            // If x falls within this subtree
            if (x <= cumulative_count + subtree_size) {
                // Adjust x to be relative to this subtree
                x -= cumulative_count;
                
                // Move to the child if it exists
                if (current->children[pos] != NULL) {
                    current = current->children[pos];
                    break;
                } else {
                    // This is a leaf or the subtree is empty
                    // This shouldn't happen in a valid (2,4) tree
                    // unless we're just counting items in the node itself
                    T = OriginalTree;
                    return ERROR;
                }
            }
            
            // x is not in this subtree, move past it
            cumulative_count += subtree_size;
            
            // If we have an item after this subtree and x points to it
            if (pos < current->Count && x == cumulative_count + 1) {
                T = OriginalTree;
                return current->items[pos]; // Found the k-th element
            }
            
            // Move past this item
            if (pos < current->Count) {
                cumulative_count += 1;
            }
            
            pos++;
            
            // If we've gone through all positions and haven't found a match
            if (pos > current->Count) {
                // Error: x is out of range for this tree
                T = OriginalTree;
                return ERROR;
            }
        }
    }

    T = OriginalTree;

    // Error: shouldn't reach here if tree is valid
    return ERROR;
}


/**  
    @brief print the (2, 4) tree in in-order traversal
    @param visit use this function to print the contains of the node
    @return none
*/
void sort(void (*visit)(Item)) {

    if (T == NULL) {
        printf("Tree is not initiallized\n");
        return;
    } else if (T->Count == 0) {
        printf("Tree is empty.\n");
        return;
    }
    
    // First print the tree structure
    printf("\n===== TREE STRUCTURE =====\n");
    print_tree_helper(T, visit, 0, "root");
    
    // Save current root
    Tree24* root = T;
    
    // Now print in-order traversal
    printf("\n===== IN-ORDER TRAVERSAL =====\n");

    in_order(root);
    printf("\n");
    
    // Restore T to root
    T = root;
    
}


/**
    @brief frees a (2, 4) Tree
    @param -
    @return -
*/
void destroy() {
    if (T == NULL) {
        fprintf(stderr, "Tree is not initiallized.\n");
        return;
    }
    
    destroyNode(T);
    T = NULL;
}

#endif