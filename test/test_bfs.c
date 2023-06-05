#include "../include/bfs.h"
#include <stdio.h>

#ifdef USE_MATRIX_IMPLEMENTATION
#include "../include/adjacency_matrix.h"
#elif USE_LIST_IMPLEMENTATION
#include "../include/adjacency_list.h"
#endif

int main() {
  // Create a graph
  Graph graph;
  int numVertices = 5;
  init_graph(&graph, numVertices);

  // Add edges to the graph
  add_edge(&graph, 0, 1, 1);
  add_edge(&graph, 0, 2, 1);
  add_edge(&graph, 0, 3, 1);
  add_edge(&graph, 1, 3, 1);
  add_edge(&graph, 2, 3, 1);
  add_edge(&graph, 3, 4, 1);

  // Perform DFS
  int initialVertex = 0;
  printf("BFS Traversal:\n");
  bfs(&graph, initialVertex);

  // Free the graph
  free_graph(&graph);

  return 0;
}
