#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

/**
 * @file UndirectedGraph.h
 * @author Anastasia Maria Marinakou | sdi2400120
 * @details course : Data Structures and Programming Techniques | Spring 2025
 * @brief header file for UndirectedGraph.c 
*/

#include <stdlib.h>
#include <stdio.h>

#define MAXVERTEX 20

typedef int Vertex;
typedef struct edge Edge;
typedef struct graph Graph;

int number_of_vertices(Graph *);
void destroy_graph(Graph *);
void print_paths(Edge **, Vertex, int);
void free_paths(Edge **, int);

Graph * Initialize();
Graph * InsertEdge(Graph *, Vertex, Vertex);
void ShowGraph(Graph *);
void BreadthFirst(Graph *, Vertex);
int IsConnected(Graph *);
Edge ** ShortestPaths(Graph *, Vertex);
void ConnectedComponents(Graph *);

#endif