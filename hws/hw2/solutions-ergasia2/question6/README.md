# Question6


## Overview

This is the last question of the second project for this course. In this exercise, we had to implement a KD Tree (k-dimensional Tree, specifically 2d-tree).

Based on the theory from the book ([Computational Geometry: Algorithms and Applications](https://link.springer.com/book/10.1007/978-3-540-77974-2)) and the Interfaces that were provided, I created the following files:

- For the KD Tree:
    - #### [`kdTreeImplementation.c`](#kdtreeimplementationc) : functions for the tree
    - #### `kdTreeInterface.h` : tree structure definition, function prototypes from `kdTreeImplementation.c`

- For the Ranges:
    - #### [`RangeImplementation.c`](#rangeimplementationc) : functions for the ranges
    - #### `RangeInterface.h` : range structure definition, function prototypes from `RangeImplementation.c`

- For the Points:
    - #### [`PointImplementation.c`](#pointimplementationc) : functions for the points
    - #### `PointInterface.h` : point structure definition, function prototypes from `PointImplementation.c`

- For the List (recycled from hw1):
    - #### [`ListImplementation.c`](#listimplementationc) : functions for the list
    - #### `ListInterface.h` : list structure definition, function prototypes from `ListImplementation.c`

- #### [`main.c`](#mainc) : shows the tree's functionality for both core functions (`buildKDTree()`, `searchKDTree()`)

- #### [`Makefile`](#makefile) : compile the files and produce executable, `q6`

## Build and Dependencies

- ### Dependencies

    In order to run this program you will need these files:

    - `kdTreeInterface.h` (`kdTreeImplementation.c`)
    - `RangeInterface.h` (`RangeImplementation.c`)
    - `PointInterface.h` (`PointImplementation.c`)
    - `ListInterface.h` (`ListImplementation.c`)
    - `math.h`
    - `stdlib.h`
    - `stdio.h`

- ### Build

    To build the executable (q6), run this command:
    ```bash
    make
    ```

    Then to run it use the command:
    ```bash
    ./q6
    ```
    If you want to check for memory errors and leaks, run this:
    ```bash
    valgrind ./q6
    ``` 

## Functionality

### `kdTreeImplementation.c`
This file contains functions given to us: 
- `kdnode_init()`

    Allocates memory for a new KD Tree node and initiallizes its fields.

    Note that field `line` is initiallized with macro `EMPTY`, defined in `kdTreeInterface.h`, to identify it as an empty value.

- `buildKDTree()`
    
    One of the core functions of this project.

    It takes an array of points and creates the tree following the algorithm described in the book; In each recursive call, the **points are sorted** either by the x-coordinate (if the depth is even) or the y-coordinate (if the depth is odd) and then computes at which position is the median point. 
    
    The median is found by dividing the amount of points in the current array of points and rounding it to the smallest integer that is greater than it. Specifically, it is given by the formula $\lceil{n/2}\rceil$, where $n$ is the current amount of points. So a line is "drawn" at the $\lceil{n/2}\rceil$-th point **( ($\lceil{n/2}\rceil$ - 1)-th** because the array is 0 index based) based again on the depth. A **vertical** line is drawn a an even depth and a **horizontal** one at an odd depth. 

    For a node v, the left child will take all the points from the begining of the array up until the median (including that) and the right child the rest of them. 

    If v is a leaf node, only one point remaining, it stores that point.

- `searchKDTree()` 

    The other core function of this project.

    It uses the KD Tree to find which points are contained in a **specified rectangular range**. The algorithm for this function is also described in the book:

    If a leaf node has been reached, it checks if the point stored there is inside the range query. Otherwise, **calculate the region** of both the left and right children. If those regions are completely contained inside the region query, call a helper function, `ReportSubtree()`, to add to the list all the points in that subtree.

    Otherwise, if the regions intersect with range query, **call the same function ny passing the appropriate child node** (either left or right, depending on the region/regions that intersect with the range).


    
It also contains a few helper functions
- `destroyKDTree()` 

    Frees the memory allocated for all the nodes in the tree.

- `ReportSubtree()` 

    Used by `searchKDTree()` to add to a list all the pointes stored in a given subtree.

- `printVisualTree()`

    Prints a KD Tree in a way that helps understand its structure

### `RangeImplementation.c`
This file has functions used mainly by `searchKDTree()` to represent rectangular ranges, calculate regions etc. In more detail:

- `range_init()`

    Allocates memory for a new range and initializes its fields with the given values. 

- `point_in_range()`

    Checks if a point is inside a range.

- `range_intersect()`

    Checks if two ranges interesect in any way.

- The following 4 functions are symmetrical and used to calculate a child node region:

    - `intersect_square_on_x_left` 

        For splitting a region vertically and keeping the left part.

    - `intersect_square_on_x_right`

        For splitting a region vertically and keeping the right part.

    - `intersect_square_on_y_up`

        For splitting a region horizontally and keeping the upper part.

    - `intersect_square_on_y_down`

        For splitting a region horizontally and keeping the lower part.

- `print_range()`

    Helper function that prints the corner coordinates of a range. Useful for debugging.



### `PointImplementation.c`
This file doesn't contain many function, but has:

- `point_init()`
    Allocates memory for a new point and initializes its fields with the given values. 

- `point_compare_x()` & `point_compare_y`

    These two are used as comparators for the `qsort()` function used in `buildKDTree()`.

### `ListImplementation.c`
The functions in this file come from the first project.

### `main.c`
`main.c` will take points from `stdin`, build the KD Tree, using `buildKDTree()`,  and print it. After, it will ask for a range from the user and will use `searchKDTree()` to find which points given before are inside that range. In continuation it will print the list with the points and at the end free memory to avoid error and leaks.

### `Makefile`
Compile all files with flags: -Wall, -Wextra, -Werror, -pedantic and -lm, but the last one only during objective file compilation.

## Demo
```
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question6$ make
gcc -Wall -Wextra -Werror -pedantic  -c kdTreeImplementation.c -o kdTreeImplementation.o 
gcc -Wall -Wextra -Werror -pedantic  -c PointImplementation.c -o PointImplementation.o 
gcc -Wall -Wextra -Werror -pedantic  -c RangeImplementation.c -o RangeImplementation.o 
gcc -Wall -Wextra -Werror -pedantic  -c main.c -o main.o 
gcc -Wall -Wextra -Werror -pedantic  kdTreeImplementation.o ListImplementation.o PointImplementation.o RangeImplementation.o main.o -o q6 -lm
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question6$ cat input
10
2 8
4 11
4.5 6
2 14
6 13.5
10 6
7.5 9
11 7
9 14
9.5 12.5
5 10 5 10
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question6$ valgrind ./q6 < input
==123954== Memcheck, a memory error detector
==123954== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==123954== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==123954== Command: ./q6
==123954== 

>>> GIVE NUMBER OF POINTS:
>>> 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> GIVE COORDINATES:
>>> (x) >>> (y) 
>>> BUILDING KD TREE...

root6.000000
    L--- 11.000000
        L--- 4.000000
            L--- 8.000000
                L--- (2.000000, 8.000000)
                R--- (4.000000, 11.000000)
            R--- (4.500000, 6.000000)
        R--- 2.000000
            L--- (2.000000, 14.000000)
            R--- (6.000000, 13.500000)
    R--- 9.000000
        L--- 10.000000
            L--- 6.000000
                L--- (10.000000, 6.000000)
                R--- (7.500000, 9.000000)
            R--- (11.000000, 7.000000)
        R--- 9.000000
            L--- (9.000000, 14.000000)
            R--- (9.500000, 12.500000)

>>> GIVE RANGE QUERY COORDINATES:
>>> (xmin) >>> (xmax) >>> (ymin) >>> (ymax) 
>>> SEARCHING FOR POINTS INSIDE THE RANGE QUERY...

(7.500000, 9.000000) <-> (10.000000, 6.000000) -> NULL
==123954== 
==123954== HEAP SUMMARY:
==123954==     in use at exit: 0 bytes in 0 blocks
==123954==   total heap usage: 63 allocs, 63 frees, 10,968 bytes allocated
==123954== 
==123954== All heap blocks were freed -- no leaks are possible
==123954== 
==123954== For lists of detected and suppressed errors, rerun with: -s
==123954== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
sdi2400120@linux17:~/sem2/2025-ergasia2-a-reynbaw/solutions-ergasia2/question6$ 
```