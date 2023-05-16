#include "../include/adjacency_matrix.h"
#include <stdbool.h>
#include <stdio.h>

bool init_matrix(Graph *graph, int numVertices) {
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

bool is_valid_vertex(Graph *graph, int vertex) {
  return (vertex >= 0 && vertex < graph->numVertices);
}

bool add_edge(Graph *graph, int vertex1, int vertex2, Weight weight) {
  if (!is_valid_vertex(graph, vertex1) || !is_valid_vertex(graph, vertex2)) {
    fprintf(stderr,
            "Invalid vertex index. Vertex index must be within the range of 0 "
            "to %d.\n",
            graph->numVertices - 1);
    return false;
  }

  graph->numEdges++;
  graph->matrix[vertex1][vertex2] = weight;
  graph->matrix[vertex2][vertex1] = weight;

  return true;
}

bool is_edge(Graph *graph, int vertex1, int vertex2) {

  return graph->matrix[vertex1][vertex2] != EMPTY_EDGE;
}

Weight get_edge_weight(Graph *graph, int vertex1, int vertex2) {
  if (!is_valid_vertex(graph, vertex1) || !is_valid_vertex(graph, vertex2)) {
    return EMPTY_EDGE;
  }

  return graph->matrix[vertex1][vertex2];
}

bool remove_edge(Graph *graph, int vertex1, int vertex2, Weight *weight) {
  if (!is_valid_vertex(graph, vertex1) || !is_valid_vertex(graph, vertex2)) {
    fprintf(stderr,
            "Invalid vertex index. Vertex index must be within the range of 0 "
            "to %d.\n",
            graph->numVertices - 1);
    return false;
  }

  if (is_edge(graph, vertex1, vertex2)) {
    *weight = graph->matrix[vertex1][vertex2];
    graph->matrix[vertex1][vertex2] = EMPTY_EDGE;
    graph->matrix[vertex2][vertex1] = EMPTY_EDGE;
    graph->numEdges--;
    return true;
  }

  return false;
}

bool is_adjacency_list_null(Graph *graph, int vertex) {
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

int get_next_adjacent_vertex(Graph *graph, int vertex, int current_vertex) {
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

void free_graph(Graph *graph) {
  // No dynamically allocated memory in the adjacency matrix graph
  // So, no action is required to free the memory
}
