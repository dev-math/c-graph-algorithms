#include "../include/adjacency_matrix.h"
#include <stdbool.h>
#include <stdio.h>

bool init_graph(Graph *graph, int numVertices) {
  if (numVertices <= 0 || numVertices > MAX_VERTICES) {
    fprintf(
        stderr,
        "Invalid number of vertices: %d. Must be in the range of 1 to %d.\n",
        numVertices, MAX_VERTICES);
    return false;
  }

  graph->numVertices = numVertices;
  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      graph->matrix[i][j] = EMPTY_EDGE;
    }
  }

  return true;
}

bool is_valid_vertex(const Graph *graph, int vertex) {
  if (!graph) {
    fprintf(stderr, "Error: Graph is not initialized.\n");
    return false;
  }

  return (vertex >= 0 && vertex < graph->numVertices);
}

bool is_adjacency_list_null(const Graph *graph, int vertex) {
  if (!is_valid_vertex(graph, vertex)) {
    return true;
  }

  for (int i = 0; i < graph->numVertices; i++) {
    if (graph->matrix[vertex][i] != EMPTY_EDGE) {
      return false;
    }
  }

  return true;
}

Pointer get_next_adjacent_vertex(const Graph *graph, int vertex, int current_vertex) {
  if (!is_valid_vertex(graph, vertex)) {
    fprintf(stderr,
            "Invalid vertex index. Vertex index must be within the range of 0 "
            "to %d.\n",
            graph->numVertices - 1);
    return EMPTY_EDGE;
  }

  for (int i = current_vertex + 1; i < graph->numVertices; i++) {
    if (graph->matrix[vertex][i] != EMPTY_EDGE) {
      return i;
    }
  }

  return INVALID_VERTICE;
}

bool check_edge(const Graph *graph, int vertex1, int vertex2) {
  if (!is_valid_vertex(graph, vertex1) || !is_valid_vertex(graph, vertex2)) {
    fprintf(stderr,
            "Invalid vertex index. Vertex index must be within the range of 0 "
            "to %d.\n",
            graph->numVertices - 1);
    return false;
  }

  return graph->matrix[vertex1][vertex2] != EMPTY_EDGE;
}

Weight get_edge_weight(const Graph *graph, int vertex1, int vertex2) {
  if (!is_valid_vertex(graph, vertex1) || !is_valid_vertex(graph, vertex2)) {
    fprintf(stderr,
            "Invalid vertex index. Vertex index must be within the range of 0 "
            "to %d.\n",
            graph->numVertices - 1);
    return EMPTY_EDGE;
  }

  return graph->matrix[vertex1][vertex2];
}

bool add_edge(Graph *graph, int source, int destination, Weight weight) {
  if (!is_valid_vertex(graph, source) || !is_valid_vertex(graph, destination)) {
    fprintf(stderr,
            "Invalid vertex index. Vertex index must be within the range of 0 "
            "to %d.\n",
            graph->numVertices - 1);
    return false;
  }

  graph->numEdges++;
  graph->matrix[source][destination] = weight;
  graph->matrix[destination][source] = weight;

  return true;
}

bool remove_edge(Graph *graph, int source, int destination, Weight *weight) {
  if (check_edge(graph, source, destination)) {
    *weight = graph->matrix[source][destination];

    graph->numEdges--;
    graph->matrix[source][destination] = EMPTY_EDGE;
    graph->matrix[destination][source] = EMPTY_EDGE;
    return true;
  }

  return false;
}

void free_graph(Graph *graph) {
  // No dynamically allocated memory in the adjacency matrix graph
  // So, no action is required to free the memory
}
