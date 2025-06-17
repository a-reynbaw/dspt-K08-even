#ifndef WEIGHTED_UNDIRECTED_GRAPH_C
#define WEIGHTED_UNDIRECTED_GRAPH_C

/**
 * @file WeightedUndirectedGraph.c
 * @author Anastasia Maria Marinakou | sdi2400120
 * @details course : Data Structures and Programming Techniques | Spring 2025
 * @brief implementation of weighted undirected graph and Kruskal's algorithm to find the MST 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "WeightedUndirectedGraph.h"

// global variable to keep track of how many edges exist in the graph
int edge_count = 0;

typedef struct edge {
   Vertex endpoint;

   // add edge weight
   int weight;

   struct edge *nextedge;
} Edge;

struct graph {
   int n;
   Edge *firstedge[MAXVERTEX];
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
 * @brief create a 2d array containing all edges from a graph
 * @param g the graph to collecte all the edges from
 * @return a list containing the edges from g
 * @details this function is used by MinimumSpaningTree() to extract the edges from a graph
*/
int ** get_edges(Graph * g) {
    int ** edges;
    edges = (int **)malloc(edge_count * sizeof(int *));

    if (!edges) return NULL;

    for (int i = 0; i < edge_count; i++) {
        edges[i] = (int *)malloc(3 * sizeof(int));
        if (!edges[i]) return NULL;
    }

    int k = 0;
    for (int i = 0; i < g->n; i++) {
        // Save the head of the list
        // Use `temp` for traversal
        Edge * temp = g->firstedge[i]; 
        while (temp) { 
            int a, b, w;
            a = i;
            b = temp->endpoint;
            w = temp->weight;

            // Check if the edge has already been inserted
            int flag = 0;
            for (int j = 0; j < k; j++) {
                if (edges[j][0] == b && edges[j][1] == a) {
                    flag++;
                    break;
                }
            }
            if (flag) {
                // Move to the next edge
                temp = temp->nextedge; 
                continue;
            }

            // Add the edge to the array
            edges[k][0] = a;
            edges[k][1] = b;
            edges[k][2] = w;
            k++;

            // Move to the next edge
            temp = temp->nextedge; 
        }
    }

    return edges;
}

// this function is used to sort the edges in ascending order
// based on their weight

/**
 * @brief Compares edges to sort them in ascending order by weight
 */
int comp(const void* a, const void* b) {
    // Cast and dereference to get the first edge
    const int* edgeA = *(const int**)a; 

    // Cast and dereference to get the second edge
    const int* edgeB = *(const int**)b; 

    // Compare the weights (third element)
    return edgeA[2] - edgeB[2]; 
}

/**
 * @brief helper function to find the parent of a vertex
 * @param v a graph vertex
 * @param parent an array containing the parents of all vertices
 * @return v's parent
 * @note used to implement a union find data structure, useful for Kruskal's algorithm
*/
int find(int v, int parent[]) {
    while(parent[v] != -1) v = parent[v];
    return v;
}

/**
 * @brief helper function to check if two verteces are in the same set and if not, unify them
 * @param a the first vertex
 * @param b the second vertex
 * @param parent an array containing the parent - "heads" of each set
 * @param depth the depth of each set, useful to create more balanced sets and make the finding process faster
 * @return 0 if they are already inn the same set - 1 if they are not and have just been unified
 * @note used to implement a union find data structure, useful for Kruskal's algorithm
*/
int un(int a, int b, int parent[], int depth[]) {
    // find the parents for each vertex
    a = find(a, parent);
    b = find(b, parent);

    // if they are already in the same set, return 0
    if( a == b ) return 0;

    // if not, unify them and update the parents and depth
    if ( depth[a] > depth[b] ) {
        parent[b] = a;
    } else {
        if ( depth[a] == depth[b] ) depth[a]++;
        parent[a] = b;
    }

    return 1;
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
Graph * InsertEdge(Graph * g, Vertex startpoint, Vertex endpoint, int weight) {
    if (!g) return NULL;

    // reduce by one because of 0-indexing
    startpoint--;
    endpoint--;

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

    edge_count++;

    // if either of these verteces hasn't been
    // encountered before, increase the vertex
    // count (`n->g`).
    if (g->firstedge[startpoint] == NULL) g->n++;
    if (g->firstedge[endpoint] == NULL) g->n++;

    new_edge1->endpoint = endpoint;
    new_edge1->weight = weight;
    new_edge1->nextedge = NULL;

    new_edge2->endpoint = startpoint;
    new_edge2->weight = weight;
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
        // use this temp edge to save the first edge
        // in this list
        Edge * temp = g->firstedge[i];
        // increase index and vertecies numbers by one to show as
        // one indexing
        printf("%d: ", i + 1);
        while (g->firstedge[i]) {
            printf("{%d, %d}, ", g->firstedge[i]->endpoint + 1, g->firstedge[i]->weight);
            g->firstedge[i] = g->firstedge[i]->nextedge;
        }

        g->firstedge[i] = temp;
        printf("\n");
    }

    return;
}

/**
 * @brief implementation of Kruskal's Algorithm to find the MST of a graph
 * @param g The graph to find the MST for
 * @return an array containig the edges that are in the MST
*/
int ** MinimumSpanningTree(Graph * g) {
    int ** edges, ** MST_edges;
    edges = get_edges(g);


    // sort the edges in ascending order based on their weight
    qsort(edges, edge_count, sizeof(edges[0]), comp);

    // `parent[]` is used to contain parent - "heads" of each set.
    // `depth[]` is used to save the the depth of each set, useful 
    // to create more balanced sets and make the finding process faster.
    int parent[edge_count], depth[edge_count];

    // init these two arrays
    memset(parent, -1, edge_count * sizeof(int));
    memset(depth, 0, edge_count * sizeof(int));


    // use MST_edges to return all the edges that are 
    // in the Minimum Spanning Tree
    MST_edges = (int **)malloc(edge_count* sizeof(int *));
    if (!MST_edges) {
        fprintf(stderr, "Unable to allocate memory.\n");
        return NULL;
    }

    // since the MST is a tree, it will contain
    // n-1 edges, where n is the number of 
    // verteces in the graph.
    for (int i = 0; i < g->n - 1; i++) {
        MST_edges[i] = (int *)malloc(3 * sizeof(int));
        if (!MST_edges[i]) {
            fprintf(stderr, "Unable to allocate memory.\n");
            return NULL;
        }
    }

    // use this to keep count of edges inserted
    // in the MST
    int k = 0;
    //int min_cost = 0;
    for (int i = 0; i < edge_count; i++) {
        if (un(edges[i][0], edges[i][1], parent, depth)) {
            //min_cost += edges[i][2];
            // add this edge to the MST
            MST_edges[k][0] = edges[i][0];
            MST_edges[k][1] = edges[i][1];
            MST_edges[k][2] = edges[i][2];
            k++;
        }
    }

    // free the array used for all the edges before returning
    for (int i = 0; i < edge_count; i++) free(edges[i]);
    free(edges);

    //return min_cost;
    return MST_edges;
}

#endif