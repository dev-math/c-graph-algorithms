#include "adj_matrix.h"
#include <stdio.h>

bool init_matrix(Graph *graph, int numVertices) {
  if (numVertices > MAX_VERTICES || numVertices <= 0) {
    fprintf(stderr, "Mensagem de erro");
    return false;
  }

  graph->numVertices = numVertices;
  graph->numEdges = 0;
  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      graph->matrix[i][j] = EMPTY_EDGE;
    }
  }

  return true;
}

int main() {
  Graph g;
  init_matrix(&g, 10);
  return 0;
}
