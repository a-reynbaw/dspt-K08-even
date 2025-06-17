#ifndef WEIGHTED_UNDIRECTED_GRAPH_H
#define WEIGHTED_UNDIRECTED_GRAPH_H

/**
 * @file WeightedUndirectedGraph.h
 * @author Anastasia Maria Marinakou | sdi2400120
 * @details course : Data Structures and Programming Techniques | Spring 2025
 * @brief header file for WeightedUndirectedGraph.c
*/

#define MAXVERTEX 20

typedef struct graph Graph;
typedef int Vertex;

int number_of_vertices(Graph *);

Graph * Initialize();
Graph * InsertEdge(Graph *, Vertex, Vertex, int);
void ShowGraph(Graph *);
int ** MinimumSpanningTree(Graph *);

void destroy_graph(Graph *);

#endif