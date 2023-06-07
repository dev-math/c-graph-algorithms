#include "../include/prim.h"
#include <stdio.h>

int main() {
  Graph graph;
  int numVertices = 5;
  init_graph(&graph, numVertices);

  add_edge(&graph, 0, 1, 2);
  add_edge(&graph, 0, 2, 3);
  add_edge(&graph, 1, 2, 4);
  add_edge(&graph, 1, 3, 1);
  add_edge(&graph, 2, 3, 5);
  add_edge(&graph, 2, 4, 4);
  add_edge(&graph, 3, 4, 3);

  Graph mst = mst_prim(&graph, 0);

  print_graph(&mst);

  free_graph(&graph);
  free_graph(&mst);

  return 0;
}
