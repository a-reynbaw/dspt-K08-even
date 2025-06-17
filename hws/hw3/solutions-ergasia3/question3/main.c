#ifndef MAIN_C
#define MAIN_C

/**
 * @file main.c
 * @author Anastasia Maria Marinakou | sdi2400120
 * @details course : Data Structures and Programming Techniques | Spring 2025
 * @brief main function to demonstrate the functionality of UndirectedGraph.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "UndirectedGraph.h"

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Invalid number of edges.\n");
        return 1;
    } else if (n > MAXVERTEX) {
        fprintf(stderr, "Error: Too many vertices (MAX = 20).\n");
        return 1;
    }

    Graph * g = Initialize();
    if (!g) return 1;

    int a, b;

    while(scanf("%d-%d", &a, &b) > 0) {
        InsertEdge(g, a, b);
    }

    printf("\n\nTHE GRAPH (adjacency list form):\n");
    ShowGraph(g);

    printf("\n\nBREADTH-FIRST TRAVERSAL AND EDGE CLASSIFICATION: \n");
    // starting from vertex 0, which is vertex 1, but
    // in 0-indexing
    BreadthFirst(g, 1);

    int ans = IsConnected(g);

    printf("\n\nGRAPH CONNECTION: \n");
    (ans) ? printf("The graph is connected.\n") : printf("The graph is not connected.\n");

    printf("\n\nFINDING SHORTEST PATHS TO ALL OTHER VERTICES:\n");
    Vertex v = 0;
    
    Edge ** paths = ShortestPaths(g, v);

    print_paths(paths, v, number_of_vertices(g));

    ConnectedComponents(g);

    free_paths(paths, number_of_vertices(g));
    destroy_graph(g);
    return 0;
}



#endif