# Question5

### Overview

This part of the project implements a **Weighted Undirected Graph** and uses **Kruskal's Algorithm** to find the **Minimum Spanning Tree (MST)**. The implementation includes functions for graph initialization, edge insertion, graph traversal, and MST computation. The solution is modular, with separate files for the implementation, interface, and demonstration.

This solution comes with the following files:

1. #### [`WeightedUndirectedGraph.h`](#weightedundirectedgraphh)

2. #### [`WeightedUndirectedGraph.c`](#weightedundirectedgraphc)

3. #### [`main.c`](#mainc)

4. #### [`Makefile`](#makefile)

---

### Build and Dependencies

- **Dependencies**

    In order to run this program, you will need the following files:

    - `WeightedUndirectedGraph.h` (`WeightedUndirectedGraph.c`)
    - `stdlib.h`
    - `stdio.h`
    - `string.h`

- **Build**

    To build the executable (`q5`), run this command:
    ```bash
    make
    ```

    Then to run it, use the command:
    ```bash
    ./q5 < input
    ```

    If you want to check for memory errors and leaks, run this:
    ```bash
    valgrind ./q5 < input
    ```

---

### Functionality

In this section, I will explain how each of the files functions.

---

#### 1. [WeightedUndirectedGraph.h]

This file defines the interface for the **Weighted Undirected Graph**. It includes the following:

- **Graph Structure**:
    - `typedef struct graph Graph;`
    - `typedef int Vertex;`
    The actual structure is declared in `WeightedUndirectedGraph.c` in order to achieve good information hiding.

- **Function Prototypes**:
    - `Graph * Initialize();`
        - Initializes an empty graph.
    - `Graph * InsertEdge(Graph *, Vertex, Vertex, int);`
        - Inserts an edge between two vertices with a given weight.
    - `void ShowGraph(Graph *);`
        - Prints the adjacency list representation of the graph.
    - `int ** MinimumSpanningTree(Graph *);`
        - Computes the MST using Kruskal's Algorithm and returns the edges in the MST.
    - `void destroy_graph(Graph *);`
        - Frees all memory allocated for the graph.

---

#### 2. [WeightedUndirectedGraph.c]

This file contains the implementation of the **Weighted Undirected Graph** and **Kruskal's Algorithm**. It includes the following:

- **Utilities**:
    - `number_of_vertices(Graph * g)`
        - Returns the number of vertices in the graph.
    - `get_edges(Graph * g)`
        - Extracts all edges from the graph into a 2D array for sorting and MST computation.
    - `comp(const void *a, const void *b)`
        - Comparator function for sorting edges by weight.
    - `find(int v, int parent[])`
        - Finds the root of a vertex in the disjoint set (used in Kruskal's Algorithm).
    - `un(int a, int b, int parent[], int depth[])`
        - Unifies two sets in the disjoint set (used in Kruskal's Algorithm).

- **Core Functions**:
    - `Graph * Initialize()`
        - Allocates memory for a new graph and initializes its adjacency list.
    - `Graph * InsertEdge(Graph * g, Vertex startpoint, Vertex endpoint, int weight)`
        - Inserts an edge into the graph. Since the graph is undirected, two edges are added (one for each direction).
    - `void ShowGraph(Graph * g)`
        - Prints the adjacency list representation of the graph.
    - `int ** MinimumSpanningTree(Graph * g)`
        - Implements Kruskal's Algorithm to compute the MST. Returns the edges in the MST as a 2D array.
    - `void destroy_graph(Graph * g)`
        - Frees all memory allocated for the graph, including the adjacency lists and the graph structure itself.

---

#### 3. [main.c]

This file demonstrates the functionality of the **Weighted Undirected Graph** and **Kruskal's Algorithm**. It includes:

- **Input Parsing**:
    - `parse_edge(char buffer[], int *a, int *b, int *w)`
        - Parses a line of input in the format `a-b-w` and extracts the vertices (`a`, `b`) and the weight (`w`).

- **Main Function**:
    - Reads the number of edges and the edges themselves from standard input.
    - Initializes the graph and inserts the edges.
    - Prints the adjacency list representation of the graph.
    - Computes the MST using Kruskal's Algorithm and prints the edges in the MST along with the total cost.
    - Frees all allocated memory before exiting.

---

#### 4. [Makefile]

The [Makefile] automates the build process for the project. It includes the following:

- **Compiler**:
    - `gcc` is used as the compiler.

- **Compiler Flags**:
    - `-Wall -Werror -Wextra -pedantic` are used for warnings and strict compliance with the C standard.

- **Rules**:
    - `$(PROGRAM): $(OBJS)`
        - Builds the executable (`q5`) from the object files.
    - `%.o: %.c $(HEADERS)`
        - Compiles `.c` files into `.o` files, ensuring header dependencies.
    - `clean`
        - Removes the executable and object files.

---

**Example Input**:
```
$ make
gcc -Wall -Werror -Wextra -pedantic -c main.c -o main.o
gcc -Wall -Werror -Wextra -pedantic -c WeightedUndirectedGraph.c -o WeightedUndirectedGraph.o
gcc -Wall -Werror -Wextra -pedantic main.o WeightedUndirectedGraph.o -o q5
$ cat input
6
1-2-50
1-3-80
2-3-60
2-4-20
3-5-40
2-5-30
4-5-10
4-6-10
$ valgrind ./q5 < input
==54630== Memcheck, a memory error detector
==54630== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==54630== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==54630== Command: ./q5
==54630== 
1: {2, 50}, {3, 80}, 
2: {1, 50}, {3, 60}, {4, 20}, {5, 30}, 
3: {1, 80}, {2, 60}, {5, 40}, 
4: {2, 20}, {5, 10}, {6, 10}, 
5: {3, 40}, {2, 30}, {4, 10}, {6, 50}, 
6: {4, 10}, {5, 50}, 
Edges in the Minimum Spanning Tree: (vertex 1 - vertex 2) , weight
> > > 4 - 5 , 10
> > > 4 - 6 , 10
> > > 2 - 4 , 20
> > > 3 - 5 , 40
> > > 1 - 2 , 50
Minimum cost: 130
==54630== 
==54630== HEAP SUMMARY:
==54630==     in use at exit: 0 bytes in 0 blocks
==54630==   total heap usage: 37 allocs, 37 frees, 5,888 bytes allocated
==54630== 
==54630== All heap blocks were freed -- no leaks are possible
==54630== 
==54630== For lists of detected and suppressed errors, rerun with: -s
==54630== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
