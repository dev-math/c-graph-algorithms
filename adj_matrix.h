#ifndef ADJ_MATRIX_H 
#define ADJ_MATRIX_H

#include <stdbool.h>

#define MAX_VERTICES 100
#define EMPTY_EDGE false;

typedef struct Graph {
  int numVertices;
  int numEdges;
  int matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph *graph, int num_nodes);
void add_edge(Graph *graph, int node1, int node2);
void remove_edge(Graph *graph, int node1, int node2);
int is_edge(Graph *graph, int node1, int node2);

#endif
