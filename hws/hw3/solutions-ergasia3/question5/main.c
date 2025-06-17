#ifndef MAIN_C
#define MAIN_C

/**
 * @file main.c
 * @author Anastasia Maria Marinakou | sdi2400120
 * @details course : Data Structures and Programming Techniques | Spring 2025
 * @brief main function to demonstrate the functionality of WeightedUndirectedGraph.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "WeightedUndirectedGraph.h"

/**
 * @brief Parses a line containing edge data in the format "a-b-w".
 * @param buffer The buffer containing the line to parse.
 * @param a Pointer to store the first vertex.
 * @param b Pointer to store the second vertex.
 * @param w Pointer to store the weight of the edge.
 */
void parse_edge(char buffer[], int *a, int *b, int *w) {
    // Remove the newline character if it exists
    buffer[strcspn(buffer, "\n")] = '\0';

    // Tokenize the buffer
    char *token = strtok(buffer, "-");
    if (token == NULL) {
        fprintf(stderr, "Error: Invalid input format (missing first vertex).\n");
        exit(EXIT_FAILURE);
    }
    *a = atoi(token);

    token = strtok(NULL, "-");
    if (token == NULL) {
        fprintf(stderr, "Error: Invalid input format (missing second vertex).\n");
        exit(EXIT_FAILURE);
    }
    *b = atoi(token);

    token = strtok(NULL, "-");
    if (token == NULL) {
        fprintf(stderr, "Error: Invalid input format (missing weight).\n");
        exit(EXIT_FAILURE);
    }
    *w = atoi(token);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Invalid number of edges.\n");
        return 1;
    } else if (n > MAXVERTEX) {
        fprintf(stderr, "Error: Too many verteces (MAX = 20).\n");
        return 1;
    }

    Graph * g = Initialize();
    if (!g) return 1;

    //char buffer[50];
    int a, b, w;

    while (scanf("%d-%d-%d", &a, &b, &w) > 0) {
        g = InsertEdge(g, a, b, w);
    }

    ShowGraph(g);

    int ** MST = MinimumSpanningTree(g);
    int min_cost = 0;

    printf("Edges in the Minimum Spanning Tree: (vertex 1 - vertex 2) , weight\n");
    for (int i = 0; i < number_of_vertices(g) - 1; i++) {
        printf("> > > %d - %d , %d\n", MST[i][0] + 1, MST[i][1] + 1, MST[i][2]);
        min_cost += MST[i][2];
    }

    printf("Minimum cost: %d\n", min_cost);

    // free all the memory allocated space
    for (int i = 0; i < number_of_vertices(g) - 1; i++) free(MST[i]);

    free(MST);

    destroy_graph(g);

    return 0;
}

#endif