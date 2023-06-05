#include "../include/dfs.h"
#include <stdio.h>
#include <stdlib.h>

void dfs_recursive(const Graph *graph, int initialVertex,
                   Pointer initialVertexPtr, bool *visited) {
  printf("Visited vertex: %d\n", initialVertex); // visit vertex
  visited[initialVertex] = VISITED;

  Pointer adjacentVertex =
      get_next_adjacent_vertex(graph, initialVertex, INVALID_VERTEX);

  while (adjacentVertex != INVALID_VERTEX) {
    int adjacentIndex =
        get_destination_vertex(graph, initialVertex, adjacentVertex);
    if (visited[adjacentIndex] == UNVISITED) {
      dfs_recursive(graph, adjacentIndex, adjacentVertex, visited);
    }

    adjacentVertex =
        get_next_adjacent_vertex(graph, initialVertex, adjacentVertex);
  }
}

void dfs(const Graph *graph, int initialVertex) {
  bool visited[graph->numVertices];
  for (int i = 0; i < graph->numVertices; i++) {
    visited[i] = UNVISITED;
  }

  Pointer initialVertexPtr = get_vertex_ptr(graph, initialVertex);

  dfs_recursive(graph, initialVertex, initialVertexPtr, visited);
}
