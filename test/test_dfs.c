#include "../include/dfs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  // Create a graph with 6 vertices
  Graph graph;
  init_graph(&graph, 6);

  // Add edges to the graph
  add_edge(&graph, 0, 1, 1);
  add_edge(&graph, 0, 2, 1);
  add_edge(&graph, 1, 3, 1);
  add_edge(&graph, 2, 4, 1);
  add_edge(&graph, 3, 5, 1);
  add_edge(&graph, 4, 5, 1);

  printf("Graph:\n");
  print_graph(&graph);

  // Perform DFS traversal
  printf("DFS traversal:\n");
  DFS(&graph);

  return 0;
}
