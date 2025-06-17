# Question5

## Overview

This is the fifth question of the second project for this course. In this exercise, we implemented a (2, 4) Tree (also known as a 2-3-4 Tree), a self-balancing search tree.

Based on the theory from the course and the provided interfaces, the following files were created:

- For the (2, 4) Tree:
    - #### [`Tree24Implementation.c`](#tree24implementationc): Functions for the (2, 4) Tree
    - #### `Tree24Interface.h`: Tree structure definition and function prototypes from `Tree24Implementation.c`

- #### [`main.c`](#mainc): Demonstrates the functionality of the (2, 4) Tree through a menu-driven program.

- #### [`Makefile`](#makefile): Compiles the files and produces the executable, `q5`.

---

## Build and Dependencies

### Dependencies

To run this program, you will need the following files:
- `Tree24Interface.h` (`Tree24Implementation.c`)
- `stdlib.h`
- `stdio.h`

### Build

To build the executable (`q5`), run this command:
```bash
make
```

To run the program, use the command:
```bash
./q5
```

To check for memory errors and leaks, run:
```bash
valgrind ./q5
```

---

## Functionality

### `Tree24Implementation.c`

This file contains the implementation of the (2, 4) Tree, including the following functions:

#### Core Functions:
- **`init()`**:
    - Initializes the global (2, 4) Tree (`T`) by allocating memory and setting its fields to default values.

- **`insert(Item x)`**:
    - Inserts a new item into the tree while maintaining the (2, 4) Tree properties.
    - Handles node splitting when a node overflows (contains more than 3 keys).

- **`delete(Item x)`**:
    - Deletes an item from the tree while maintaining the (2, 4) Tree properties.
    - Handles node underflow by borrowing keys from siblings or merging nodes.

- **`search(Key x)`**:
    - Searches for a key in the tree and returns it if found. If the key does not exist, it returns an error.

- **`find(int x)`**:
    - Finds the x-th smallest element in the tree based on its rank.

- **`count()`**:
    - Counts the total number of keys in the tree.

- **`sort(void (*visit)(Item))`**:
    - Prints the tree structure and performs an in-order traversal to display the keys in sorted order.

- **`destroy()`**:
    - Frees all memory allocated for the tree.

#### Helper Functions:
- **`count_recursive()`**:
    - Counts recursively how many keys in total are in the tree.

- **`create_node()`**:
    - Allocates memory for a new node and initializes its fields.

- **`destroyNode(Tree24 *node)`**:
    - Recursively frees all nodes in the tree.

- **`print_tree_helper(Tree24 *node, void (*visit)(Item), int level, char* path)`**:
    - Prints the tree structure with proper indentation.

- **`in_order(Tree24 *node)`**:
    - Performs an in-order traversal of the tree.

- **`visit(Item i)`**:
    - Prints a single item. Used as a callback function for traversal.

---

### `main.c`

The `main.c` file demonstrates the functionality of the (2, 4) Tree through a menu-driven program. The following operations are supported:

1. **Insert**:
    - Prompts the user to enter an item to insert into the tree.

2. **Delete**:
    - Prompts the user to enter an item to delete from the tree.

3. **Search**:
    - Prompts the user to enter a key to search for in the tree. Displays whether the key exists in the tree.

4. **Find**:
    - Prompts the user to enter a rank (`k`) and finds the k-th smallest item in the tree.

5. **Sort**:
    - Displays the tree structure and performs an in-order traversal to print the keys in sorted order.

6. **Count**:
    - Displays the total number of keys in the tree.

7. **Exit**:
    - Frees all memory allocated for the tree and exits the program.

---

## Demo

### Simple Example Run:
```
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question5$ valgrind ./q5 
==131180== Memcheck, a memory error detector
==131180== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==131180== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==131180== Command: ./q5
==131180== 

*************
Creating Tree...

Tree Created!
*************

========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 1
Enter item to insert: 4
Inserted 4
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 1
Enter item to insert: 6
Inserted 6
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 1
Enter item to insert: 12
Inserted 12
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 1
Enter item to insert: 15
Inserted 15
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 1
Enter item to insert: 8
Inserted 8
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 1
Enter item to insert: 11
Inserted 11
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 5

===== TREE STRUCTURE =====
[root] Node(2 keys): 8 12 
    [root.0] Node(2 keys): 4 6 
    [root.1] Node(1 keys): 11 
    [root.2] Node(1 keys): 15 

===== IN-ORDER TRAVERSAL =====
4 6 8 11 12 15 
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 6
Total key count: 6
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 4
Enter k to find the k-th smallest item: 5
The 5-th smallest item is 12
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 3
Enter item to search: 2
2 is not in the tree
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 3
Enter item to search: 6
6 is in the tree
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 2
Enter item to delete: 4
Deleted 4
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 2
Enter item to delete: 6
Deleted 6
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 5

===== TREE STRUCTURE =====
[root] Node(1 keys): 12 
    [root.0] Node(2 keys): 8 11 
    [root.1] Node(1 keys): 15 

===== IN-ORDER TRAVERSAL =====
8 11 12 15 
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 2
Enter item to delete: 1
Item is not in the Tree and cannot be deleted.
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 
2
Enter item to delete: 11
Deleted 11
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 5

===== TREE STRUCTURE =====
[root] Node(1 keys): 12 
    [root.0] Node(1 keys): 8 
    [root.1] Node(1 keys): 15 

===== IN-ORDER TRAVERSAL =====
8 12 15 
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 2
Enter item to delete: 12
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 2
Enter item to delete: 8
Deleted 8
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 5

===== TREE STRUCTURE =====
[root] Node(1 keys): 15 

===== IN-ORDER TRAVERSAL =====
15 
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 2
Enter item to delete: 15
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 5
Tree is not initiallized
========= MENU =========
1. Insert
2. Delete
3. Search
4. Find
5. Sort
6. Count
7. Exit
========================
Enter your choice: 7
Tree is not initiallized.
==131180== 
==131180== HEAP SUMMARY:
==131180==     in use at exit: 0 bytes in 0 blocks
==131180==   total heap usage: 6 allocs, 6 frees, 2,432 bytes allocated
==131180== 
==131180== All heap blocks were freed -- no leaks are possible
==131180== 
==131180== For lists of detected and suppressed errors, rerun with: -s
==131180== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

---

## Notes

- The program ensures that the (2, 4) Tree properties are maintained during insertion and deletion.
- The `find()` function efficiently retrieves the k-th smallest element using subtree sizes.
- The `sort()` function provides a clear visualization of the tree structure and its in-order traversal.
- Memory is properly managed, and the program can be tested for leaks using `valgrind`.
