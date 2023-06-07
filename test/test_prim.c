#include "../include/prim.h"
#include <stdio.h>

void printMST(const Graph *graph, const Graph *mst) {
  printf("Minimum Spanning Tree:\n");
  printf("Edge \tWeight\n");
  for (int v = 1; v < mst->numVertices; v++) {
    int u = mst->adjacency_list[v]->destination;
    Weight weight = mst->adjacency_list[v]->weight;
    printf("%d - %d \t%.2lf\n", u, v, weight);
  }
}

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

  printMST(&graph, &mst);

  free_graph(&graph);
  free_graph(&mst);

  return 0;
}
