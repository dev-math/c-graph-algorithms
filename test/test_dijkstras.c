#include "../include/dijkstras.h"
#include <stdio.h>

int main() {
  Graph graph;
  int numVertices = 5;
  init_graph(&graph, numVertices);

  add_edge(&graph, 0, 1, 6);
  add_edge(&graph, 0, 3, 1);
  add_edge(&graph, 1, 3, 2);
  add_edge(&graph, 1, 4, 2);
  add_edge(&graph, 1, 2, 5);
  add_edge(&graph, 2, 4, 5);
  add_edge(&graph, 3, 4, 1);

  dijkstra(&graph, 0);

  add_edge(&graph, 3, 4, 1);

  free_graph(&graph);

  return 0;
}
