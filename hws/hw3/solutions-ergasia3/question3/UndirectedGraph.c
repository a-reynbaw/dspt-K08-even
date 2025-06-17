#ifndef UNDIRECTED_GRAPH_C
#define UNDIRECTED_GRAPH_C

/**
 * @file UndirectedGraph.c
 * @author Anastasia Maria Marinakou | sdi2400120
 * @details course : Data Structures and Programming Techniques | Spring 2025
 * @brief implementation of an undirected graph and various functions
*/

#include <stdlib.h>
#include <stdio.h>
#include "UndirectedGraph.h"
#include "queues/sedgewick/QUEUE.h"
#include "queues/sedgewick/Item.h"


/**
 * @struct edge
 * @brief use to represent an undirected graph edge when the graph is represented using adjacency lists
 * @param endpoint the ending vertex of the edge
 * @param nextedge pointer to the next edge in the list
 * @note no need to represent the starting vertex, since the adjacency list is an array of lists, so the starting vertex is paralel to the index of the list in the array
*/
struct edge {
   Vertex endpoint;

   struct edge * nextedge;
};

/**
 * @struct graph
 * @brief undirected graph data structure
 * @param n the amount of vertices in the graph
 * @param firstedge adjacency list representing the connections between vertices in the graph.
 * @note the adjacency list is an array of lists, so the index in the array is the starting vertex and all the vertices in the i-th list of the array are the ones that connect to the i-th vertex.
*/
struct graph {
   int n;

   Edge * firstedge[MAXVERTEX];
};

/* utilities */

/**
 * @brief use this function to gain access to the amount of vertices in a graph
 * @param g a graph 
 * @return the amount of vertices g contains
*/
int number_of_vertices(Graph * g) {
    return g->n;
}

/**
 * @brief Used to free a graph
 * @param g The graph to be freed
 * @return -
*/
void destroy_graph(Graph * g) {
    if (!g) return;

    // Traverse each adjacency list
    for (int i = 0; i < MAXVERTEX; i++) {
        Edge *current = g->firstedge[i];
        while (current) {
            // save the next edge
            Edge *next = current->nextedge;
            // free the current edge 
            free(current);                 
            // move to the next edge
            current = next;                
        }
    }

    // Free the graph structure itself
    free(g);

    return;
}

/**
 * @brief helper function to print the shortest paths starting from a vertex,created by ShortestPaths()
 * @param paths array of lists containing the paths
 * @param v starting vertex
 * @param graph_size total amount of vertices in the graph
 * @returns -
*/
void print_paths(Edge ** paths, Vertex v, int graph_size) {
    printf("\nSTARTING FROM VERTEX %d\n", v + 1);

    for (int i = 0; i < graph_size; i++) {
        /* 
            this condition checks for uninitialized vertices, meaning that a vertex
            with "id" `i` is not contained in the graph. very good too handle
            both 0 and 1 indexing.
        */
        if (paths[i] == NULL) continue;

        if (i == v) continue;

        printf("\nSHORTEST PATH TO VERTEX %d:\n", i + 1);

        if (paths[i] == NULL) {
            printf("NON-EXISTANT\n");
        } else {
            // save the starting edge to recover after list traversal
            Edge * temp = paths[i];

            while (paths[i]) {
                // print path
                (paths[i]->nextedge) ? printf("%d -> ", paths[i]->endpoint + 1) : printf("%d", paths[i]->endpoint + 1);

                // move forward to the next vertex in the path
                paths[i] = paths[i]->nextedge;
            }

            paths[i] = temp;
        }

        printf("\n");
    }
}


/**
 * @brief helper function to free the array created by ShortestPaths()
 * @param paths the array contaning the paths
 * @param graph_size the amount of vertices in the graph
 * @returns -
*/
void free_paths(Edge ** paths, int graph_size) {
    if (!paths) return;

    for (int i = 0; i < graph_size; i++) {
        if (paths[i] == NULL) continue;

        Edge * current = paths[i];
        while (current) {
            // save the next edge
            Edge * next = current->nextedge;
            // free the current edge 
            free(current);                 
            // move to the next edge
            current = next;                
        }
    }
    free(paths);
}

/* core functions */

/**
 * @brief initialiazes a graph
 * @return the initialized graph
*/
Graph * Initialize() {
    Graph * g = (Graph *)malloc(sizeof(struct graph));

    if (!g) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    g->n = 0;

    /*
       initlialize all the lists as NULL, in order
       to recognize if a vertex is in the graph.
    */
    for (int i = 0; i < MAXVERTEX; i++) {
        g->firstedge[i] = NULL;
    }

    return g;
}

/**
 * @brief inserts a new edge to the graph
 * @param g a graph
 * @param startpoint the Vertex from where the edge begins
 * @param endpoint the Vertex where the edge ends
 * @return the updated graph
*/
Graph * InsertEdge(Graph * g, Vertex startpoint, Vertex endpoint) {
    if (!g) return NULL;

    // reduce by one because of 0-indexing
    // startpoint--;
    // endpoint--;

    // the graph is undericted, so add two edges: one starting
    // from startpoint and one starting from end point.
    Edge * new_edge1 = (Edge *)malloc(sizeof(struct edge));

    if (!new_edge1) {
        fprintf(stderr, "Unable to allocate memory\n");
        return NULL;
    }

    Edge * new_edge2 = (Edge *)malloc(sizeof(struct edge));

    if (!new_edge2) {
        fprintf(stderr, "Unable to allocate memory\n");
        return NULL;
    }

    // if either of these vertices hasn't been
    // encountered before, increase the vertex
    // count (`n->g`).
    if (g->firstedge[startpoint] == NULL) g->n++;
    if (g->firstedge[endpoint] == NULL) g->n++;

    new_edge1->endpoint = endpoint;
    new_edge1->nextedge = NULL;

    new_edge2->endpoint = startpoint;
    new_edge2->nextedge = NULL;

    // find where to add this edge
    if (g->firstedge[startpoint] == NULL)  {
        // special case: first edge starting from 
        // this vertex
        g->firstedge[startpoint] = new_edge1;
    } else {
        // otherwise, add the new edge at the end of the 
        // appropriate list

        // use this temp edge to save the address if the first edge in this list
        Edge * temp = g->firstedge[startpoint];
        // get at the last edge in the list
        while(g->firstedge[startpoint]->nextedge) {
            g->firstedge[startpoint] = g->firstedge[startpoint]->nextedge;
        }

        // and add the new edge there
        g->firstedge[startpoint]->nextedge = new_edge1;


        g->firstedge[startpoint] = temp;
    }

    if (g->firstedge[endpoint] == NULL) {
        // special case: first edge starting from 
        // this vertex
        g->firstedge[endpoint] = new_edge2;
    } else {
        // otherwise, add the new edge at the end of the 
        // appropriate list

        Edge * temp = g->firstedge[endpoint];
        // get at the last edge in the list
        while(g->firstedge[endpoint]->nextedge) {
            g->firstedge[endpoint] = g->firstedge[endpoint]->nextedge;
        }

        // and add the new edge there
        g->firstedge[endpoint]->nextedge = new_edge2;

        g->firstedge[endpoint] = temp;
    }

    return g;
}

/**
 * @brief prints a graph
 * @param g a graph 
 * @return -
*/
void ShowGraph(Graph * g) {
    if (!g) return;

    for (int i = 0; i < g->n; i++) {
        if (g->firstedge[i] == NULL) continue;

        // use this temp edge to save the first edge
        // in this list
        Edge * temp = g->firstedge[i];
        // increase index and vertecies numbers by one to show as
        // one indexing
        printf("%d: ", i);
        while (g->firstedge[i]) {
            printf("%d, ", g->firstedge[i]->endpoint);
            g->firstedge[i] = g->firstedge[i]->nextedge;
        }

        g->firstedge[i] = temp;
        printf("\n");
    }

    return;
}


/**
 * @brief performs Breadth-First Search to an Undirected Graph and classifies edges
 * @param g an undirected Graph
 * @param u a starting graph vertex 
 * @returns -
 * @note this function is an expansion of the one provided to us
 * @note the queue data structure implementation is taken from the course's website
*/
void BreadthFirst(Graph * g, Vertex u) {
    Queue Q = QUEUEinit();
    if (!Q) return;

    // reducing the starting vertex by
    // one for 0 indexing
    // u--;

    int visited[MAXVERTEX];
    int parent[MAXVERTEX]; // Track parent relationships for edge classification
    Vertex v, w;
    Edge * curr_edge;
   
    // Initialize visited array and parent array
    for (v = 0; v < g->n; v++) {
        visited[v] = 0;
        parent[v] = -1;  // -1 indicates no parent
    }
   
    // Start BFS from the specified vertex u
    // print the vertex as one indexed
    printf("Starting BFS from vertex %d\n", u + 1);
    QUEUEput(Q, u);
    visited[u] = 1;  // Mark as visited when put in queue
            
    do {
        v = QUEUEget(Q);
   
        curr_edge = g->firstedge[v];  /* curedge is a pointer to the first edge (v,_) of V */
        while (curr_edge) {
            w = curr_edge->endpoint;  /* w is a successor of v and (v,w) is the current edge */
            
            printf("Examining edge (%d, %d): ", v, w);
            
            if (!visited[w]) {
                // Tree edge - leads to an unvisited node
                printf("TREE EDGE\n");
                visited[w] = 1;  // Mark as visited when discovered
                parent[w] = v;   // Set parent relationship
                QUEUEput(Q, w);
            } else if (parent[v] != w) {
                // Cross edge - leads to an already visited node that isn't the parent
                // In undirected graphs, we exclude the edge back to the parent
                printf("CROSS EDGE\n");
            } else {
                // This is the edge back to the parent in undirected graph
                printf("PARENT EDGE (not classified)\n");
            }
            
            curr_edge = curr_edge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
        }
    } while (!QUEUEempty(Q));
    
    
    QUEUEdump(Q);
}

/**
 * @brief checks if a graph is connected through BFS traversal
 * @param g graph to check if connected
 * @returns 1: if the graph is connected, 0: if not, -1: if an error occured
*/
int IsConnected(Graph * g) {
    Queue Q = QUEUEinit();
    if (!Q) return -1;


    int visited[MAXVERTEX];
    Vertex v, w;
    Edge * curr_edge;
   
    // initialize visited array and parent array
    for (v = 0; v < g->n; v++) visited[v] = 0;
   

    // start from the first vertex
    QUEUEput(Q, 0);

    while (!QUEUEempty(Q)) {
        w = QUEUEget(Q);

        // mark vertex as visited
        visited[w] = 1;

        // save the first endpoint for this startpoint
        curr_edge = g->firstedge[w];

        // add all unvisited neighbours of w
        while (g->firstedge[w]) {
            v = g->firstedge[w]->endpoint;
            if (!visited[v]) QUEUEput(Q, v);

            g->firstedge[w] = g->firstedge[w]->nextedge;
        }
        g->firstedge[w] = curr_edge;
    }
    QUEUEdump(Q);

    int cnt = 0;

    /* 
       if the vertex has been visited, it will
       be marked with 1 in the array, otherwise it
       will be 0. so, if all it's elements are added
       we will get the amount of vertices visited 
       from the BFS traversal.
    */
    for (int i = 0; i < g->n; i++) cnt += visited[i];

    return (cnt == g->n);
}

/**
 * @brief finds the shortest paths to all vertices starting from a specific vertex, using BFS traversal
 * @param g a graph
 * @param v starting vertex
 * @return An array containing edge lists to all vertices in the graph
*/
Edge ** ShortestPaths(Graph * g, Vertex u) {
    Edge ** paths = (Edge **)malloc(sizeof(Edge *) * g->n); 
    if (!paths) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // initialize the paths array with NULL pointers
    for (int i = 0; i < g->n; i++) paths[i] = NULL;

    // create the queue for BFS traversal
    Queue Q = QUEUEinit();
    if (!Q) return NULL;

    int visited[MAXVERTEX];
    // array to track the parent of each vertex
    int parent[MAXVERTEX]; 
    Vertex v, w;
    Edge * curr_edge;

    // initialize visited and parent arrays
    for (int i = 0; i < g->n; i++) {
        visited[i] = 0;
        parent[i] = -1; // -1 indicates no parent
    }

    // start BFS from the given vertex
    QUEUEput(Q, u);
    visited[u] = 1;

    while (!QUEUEempty(Q)) {
        w = QUEUEget(Q);

        // save the first edge for this vertex
        curr_edge = g->firstedge[w];

        while (curr_edge) {
            v = curr_edge->endpoint;

            // if the vertex has not been visited, process it
            if (!visited[v]) {
                QUEUEput(Q, v);
                visited[v] = 1;
                // set the parent of v to w
                parent[v] = w; 
            }

            curr_edge = curr_edge->nextedge;
        }
    }

    // reconstruct paths using the parent array
    for (int i = 0; i < g->n; i++) {
        // skip the starting vertex and unreachable vertices
        if (i == u || parent[i] == -1) continue; 

        Vertex current = i;

        // reconstruct the path by backtracking from the current vertex to the starting vertex
        while (current != u) {
            Edge * new_edge = (Edge *)malloc(sizeof(struct edge));
            if (!new_edge) {
                fprintf(stderr, "Unable to allocate memory.\n");
                return NULL;
            }

            new_edge->endpoint = current;
            new_edge->nextedge = paths[i];
            paths[i] = new_edge;

            current = parent[current];
        }

        // add the starting vertex to the path
        Edge * new_edge = (Edge *)malloc(sizeof(struct edge));
        if (!new_edge) {
            fprintf(stderr, "Unable to allocate memory.\n");
            return NULL;
        }

        new_edge->endpoint = u;
        new_edge->nextedge = paths[i];
        paths[i] = new_edge;
    }

    QUEUEdump(Q);

    return paths;
}

/**
 * @brief finds and prints the connected components of a graph using BFS.
 * @param g the graph to analyze.
 * @returns -
*/
void ConnectedComponents(Graph * g) {
    if (!g) return;

    int * visited = (int *)malloc(sizeof(int) * MAXVERTEX);
    if (!visited) {
        fprintf(stderr, "Unable to allocate memory/\n");
        return;
    }

    Queue Q = QUEUEinit();
    if (!Q) return;

    for (int i = 0; i < g->n; i++) visited[i] = 0;

    // counter for connected components
    int component_count = 0; 

    printf("\n\nCONNECTED COMPONENTS:\n");

    // iterate over all vertices in the graph
    for (int i = 0; i < g->n; i++) {
        if (g->firstedge[i] == NULL) continue;

        // if the vertex is not visited, it belongs to a new component
        if (!visited[i]) {
            component_count++;
            printf("~ COMPONENT %d: ", component_count);

            // start BFS from this vertex
            QUEUEput(Q, i);
            visited[i] = 1;

            while (!QUEUEempty(Q)) {
                Vertex v = QUEUEget(Q);
                // print the vertex (1-indexed)
                printf("%d ", v + 1);

                // traverse the adjacency list of the current vertex
                Edge * curr_edge = g->firstedge[v];
                while (curr_edge) {
                    Vertex w = curr_edge->endpoint;

                    // if the neighbor is not visited, add it to the queue
                    if (!visited[w]) {
                        QUEUEput(Q, w);
                        visited[w] = 1;
                    }

                    curr_edge = curr_edge->nextedge;
                }
            }

            // end of the current component
            printf("\n"); 
        }
    }

    // free the queue
    QUEUEdump(Q); 

    free(visited);

    return;
}


#endif