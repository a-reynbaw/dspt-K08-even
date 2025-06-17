# Question3

### Overview

This part of the project implements an **Undirected Graph** and provides various functionalities such as **Breadth-First Search (BFS)**, **Shortest Path Calculation**, **Connected Components Detection**, and **Graph Traversal**. The implementation is modular, with separate files for the graph's interface, implementation, queue utilities, and demonstration.

This solution comes with the following files:

1. #### [`UndirectedGraph.h`](#undirectedgraphh)

2. #### [`UndirectedGraph.c`](#undirectedgraphc)

3. #### [`main.c`](#mainc)

4. #### [`Makefile`](#makefile)

5. #### [`QUEUE.h`](#queueh)

6. #### [`QImplementation.c`](#qimplementationc)

The last two files are taken from the code provided at the course's website

---

### Build and Dependencies

- **Dependencies**

    In order to run this program, you will need the following files:

    - `UndirectedGraph.h` (`UndirectedGraph.c`)
    - `QUEUE.h` (`QImplementation.c`)
    - `stdlib.h`
    - `stdio.h`

- **Build**

    To build the executable (`q3`), run this command:
    ```bash
    make
    ```

    Then to run it, use the command:
    ```bash
    ./q3 < your_input_file
    ```

    If you want to check for memory errors and leaks, run this:
    ```bash
    valgrind ./q3 < your_input_file
    ```

---

### Functionality

In this section, I will explain how each of the files functions.

---

#### 1. `UndirectedGraph.h`

This file defines the interface for the **Undirected Graph**. It includes the following:

- **Graph Structure**:
    - `typedef struct graph Graph;`
    - `typedef int Vertex;`
    - `typedef struct edge Edge;`
    The actual structure is declared in `UndirectedGraph.c` to achieve good information hiding.

- **Function Prototypes**:
    - `Graph * Initialize();`
        - Initializes an empty graph.
    - `Graph * InsertEdge(Graph *, Vertex, Vertex);`
        - Inserts an edge between two vertices.
    - `void ShowGraph(Graph *);`
        - Prints the adjacency list representation of the graph.
    - `void BreadthFirst(Graph *, Vertex);`
        - Performs BFS traversal starting from a given vertex and classifies edges.
    - `int IsConnected(Graph *);`
        - Checks if the graph is connected.
    - `Edge ** ShortestPaths(Graph *, Vertex);`
        - Finds the shortest paths from a given vertex to all other vertices using BFS.
    - `void ConnectedComponents(Graph *);`
        - Finds and prints all connected components of the graph.
    - `void destroy_graph(Graph *);`
        - Frees all memory allocated for the graph.

---

#### 2. `UndirectedGraph.c`

This file contains the implementation of the **Undirected Graph** and its associated functionalities. It includes the following:

- **Utilities**:
    - `number_of_vertices(Graph * g)`
        - Returns the number of vertices in the graph.
    - `destroy_graph(Graph * g)`
        - Frees all memory allocated for the graph, including adjacency lists and the graph structure itself.
    - `print_paths(Edge ** paths, Vertex v, int graph_size)`
        - Prints the shortest paths from a given vertex to all other vertices.
    - `free_paths(Edge ** paths, int graph_size)`
        - Frees the memory allocated for the paths array created by `ShortestPaths`.

- **Core Functions**:
    - `Graph * Initialize()`
        - Allocates memory for a new graph and initializes its adjacency list.
    - `Graph * InsertEdge(Graph * g, Vertex startpoint, Vertex endpoint)`
        - Inserts an edge into the graph. Since the graph is undirected, two edges are added (one for each direction).
    - `void ShowGraph(Graph * g)`
        - Prints the adjacency list representation of the graph.
    - `void BreadthFirst(Graph * g, Vertex u)`
        - Performs BFS traversal starting from a given vertex and classifies edges as tree edges or cross edges.
    - `int IsConnected(Graph * g)`
        - Checks if the graph is connected by performing BFS traversal.
    - `Edge ** ShortestPaths(Graph * g, Vertex u)`
        - Finds the shortest paths from a given vertex to all other vertices using BFS.
    - `void ConnectedComponents(Graph * g)`
        - Finds and prints all connected components of the graph using BFS.

---

#### 3. `QUEUE.h`

This file defines the interface for the **Queue** data structure, which is used in BFS traversal. It includes the following:

- **Queue Structure**:
    - `typedef struct queue * Queue;`

- **Function Prototypes**:
    - `Queue QUEUEinit();`
        - Initializes an empty queue.
    - `int QUEUEempty(Queue);`
        - Checks if the queue is empty.
    - `void QUEUEput(Queue, Item);`
        - Adds an item to the queue.
    - `Item QUEUEget(Queue);`
        - Removes and returns an item from the queue.
    - `void QUEUEdump(Queue);`
        - Frees all memory allocated for the queue.

---

#### 4. `QImplementation.c`

This file contains the implementation of the **Queue** data structure. It includes the following:

- **Queue Node Structure**:
    - `struct QUEUEnode`
        - Represents a node in the queue.

- **Queue Functions**:
    - `Queue QUEUEinit()`
        - Allocates memory for a new queue and initializes it.
    - `int QUEUEempty(Queue q)`
        - Returns 1 if the queue is empty, 0 otherwise.
    - `void QUEUEput(Queue q, Item item)`
        - Adds an item to the end of the queue.
    - `Item QUEUEget(Queue q)`
        - Removes and returns the item at the front of the queue.
    - `void QUEUEdump(Queue q)`
        - Frees all memory allocated for the queue.

---

#### 5. `main.c`

This file demonstrates the functionality of the **Undirected Graph** and its associated functions. It includes:

- **Input Parsing**:
    - Reads the number of edges and the edges themselves from standard input.

- **Main Function**:
    - Initializes the graph and inserts the edges.
    - Prints the adjacency list representation of the graph.
    - Performs BFS traversal and classifies edges.
    - Checks if the graph is connected.
    - Finds the shortest paths from a given vertex to all other vertices.
    - Finds and prints all connected components of the graph.
    - Frees all allocated memory before exiting.

---

#### 6. `Makefile`

The `Makefile` automates the build process for the project. It includes the following:

- **Compiler**:
    - `gcc` is used as the compiler.

- **Compiler Flags**:
    - `-Wall -Werror -Wextra -pedantic` are used for warnings and strict compliance with the C standard.

- **Rules**:
    - `$(PROGRAM): $(OBJS)`
        - Builds the executable (`q3`) from the object files.
    - `%.o: %.c $(HEADERS)`
        - Compiles `.c` files into `.o` files, ensuring header dependencies.
    - `clean`
        - Removes the executable and object files.

---

**Example Input**:
```
$ cat input
7
2-1
3-2
4-1
5-3
2-5
2-4
1-5
5-4
4-3
6-7
$ make
gcc -Wall -Werror -Wextra -pedantic -c main.c -o main.o
gcc -Wall -Werror -Wextra -pedantic -c UndirectedGraph.c -o UndirectedGraph.o
gcc -Wall -Werror -Wextra -pedantic -c queues/sedgewick/QImplementation.c -o queues/sedgewick/QImplementation.o
gcc -Wall -Werror -Wextra -pedantic main.o UndirectedGraph.o queues/sedgewick/QImplementation.o -o q3
$ valgrind ./q3 < input
==36683== Memcheck, a memory error detector
==36683== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==36683== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==36683== Command: ./q3
==36683== 


THE GRAPH (adjacency list form):
1: 2, 4, 5, 
2: 1, 3, 5, 4, 
3: 2, 5, 4, 
4: 1, 2, 5, 3, 
5: 3, 2, 1, 4, 
6: 7, 
7: 6, 


BREADTH-FIRST TRAVERSAL AND EDGE CLASSIFICATION: 
Starting BFS from vertex 1
Examining edge (1, 2): TREE EDGE
Examining edge (1, 4): TREE EDGE
Examining edge (1, 5): TREE EDGE
Examining edge (2, 1): PARENT EDGE (not classified)
Examining edge (2, 3): TREE EDGE
Examining edge (2, 5): CROSS EDGE
Examining edge (2, 4): CROSS EDGE
Examining edge (4, 1): PARENT EDGE (not classified)
Examining edge (4, 2): CROSS EDGE
Examining edge (4, 5): CROSS EDGE
Examining edge (4, 3): CROSS EDGE
Examining edge (5, 3): CROSS EDGE
Examining edge (5, 2): CROSS EDGE
Examining edge (5, 1): PARENT EDGE (not classified)
Examining edge (5, 4): CROSS EDGE
Examining edge (3, 2): PARENT EDGE (not classified)
Examining edge (3, 5): CROSS EDGE
Examining edge (3, 4): CROSS EDGE


GRAPH CONNECTION: 
The graph is not connected.


FINDING SHORTEST PATHS TO ALL OTHER VERTICES:
STARTING FROM VERTEX 1

SHORTEST PATH TO VERTEX 2:
1 -> 2

SHORTEST PATH TO VERTEX 3:
1 -> 2 -> 3

SHORTEST PATH TO VERTEX 4:
1 -> 4

SHORTEST PATH TO VERTEX 5:
1 -> 5

SHORTEST PATH TO VERTEX 6:
NON-EXISTANT


SHORTEST PATH TO VERTEX 7:
NON-EXISTANT



CONNECTED COMPONENTS:
~ COMPONENT 1: 1 2 4 5 3 
~ COMPONENT 2: 6 7 
==36683== 
==36683== HEAP SUMMARY:
==36683==     in use at exit: 0 bytes in 0 blocks
==36683==   total heap usage: 64 allocs, 64 frees, 6,304 bytes allocated
==36683== 
==36683== All heap blocks were freed -- no leaks are possible
==36683== 
==36683== For lists of detected and suppressed errors, rerun with: -s
==36683== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```