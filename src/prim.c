#include "../include/prim.h"
#include "../include/heap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Graph mst_prim(Graph *graph, int initialVertex) {
  int numVertices = graph->numVertices;
  int key[numVertices];    // Store the key values (weights) of each vertex
  int parent[numVertices]; // Store the parent of each vertex in the MST
  bool visited[numVertices];

  Graph mst;
  init_graph(&mst, numVertices);

  Heap heap;
  init_heap(&heap, numVertices);

  for (int i = 0; i < numVertices; i++) {
    visited[i] = UNVISITED;
    key[i] = INFINITY_POS;
    parent[i] = -1;

    heap.array[i].vertex = i;
    heap.array[i].key = key[i];
  }

  key[0] = 0;
  parent[0] = -1;

  while (!is_heap_empty(&heap)) {
    int u = extract_min(&heap);
    visited[u] = true;

    Pointer adjacentVertex = get_next_adjacent_vertex(graph, u, INVALID_VERTEX);
    while (adjacentVertex != INVALID_VERTEX) {
      int v = get_destination_vertex(graph, u, adjacentVertex);
      Weight weight = get_edge_weight(graph, u, v);

      if (!visited[v] && weight < key[v]) {
        parent[v] = u;
        key[v] = weight;
        decrease_key(&heap, v, weight);
      }

      adjacentVertex = get_next_adjacent_vertex(graph, u, adjacentVertex);
    }
  }

  for (int i = 1; i < numVertices; i++) {
    add_edge(&mst, parent[i], i, key[i]);
  }

  free_heap(&heap);

  return mst;
}
