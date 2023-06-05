#include "../include/adjacency_list.h"
#include <stdio.h>
#include <stdlib.h>

bool init_graph(Graph *graph, int numVertices) {
  if (numVertices <= 0) {
    fprintf(stderr, "Invalid number of vertices.\n");
    return false;
  }

  graph->numVertices = numVertices;
  graph->adjacency_list = (Pointer *)calloc(numVertices, sizeof(Pointer));
  if (graph->adjacency_list == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return false;
  }

  return true;
}

bool is_valid_graph(const Graph *graph) {
  if (!graph) {
    fprintf(stderr, "Error: Graph is not initialized.\n");
    return false;
  }
  return true;
}

bool is_valid_vertex(const Graph *graph, int vertex) {
  if (vertex < 0 || vertex > graph->numVertices) {
    fprintf(stderr,
            "Invalid vertex index. Vertex index must be within the range of 0 "
            "to %d.\n",
            graph->numVertices - 1);
    return false;
  }

  return true;
}

bool is_adjacency_list_null(const Graph *graph, int vertex) {
  if (!is_valid_graph(graph) || !is_valid_vertex(graph, vertex)) {
    return true;
  }
  return (graph->adjacency_list[vertex] == NULL);
}

Pointer get_next_adjacent_vertex(const Graph *graph, int vertex,
                                 Pointer current_vertex) {
  if (!is_valid_graph(graph) || !is_valid_vertex(graph, vertex) ||
      is_adjacency_list_null(graph, vertex)) {
    return INVALID_VERTEX;
  }

  Pointer next_adjacent =
      current_vertex ? current_vertex->next : graph->adjacency_list[vertex];
  return next_adjacent;
}

bool check_edge(const Graph *graph, int vertex1, int vertex2) {
  if (!is_valid_graph(graph) || !is_valid_vertex(graph, vertex1) ||
      !is_valid_vertex(graph, vertex2)) {
    return false;
  }

  Pointer edge = graph->adjacency_list[vertex1];
  while (edge != NULL) {
    if (edge->destination == vertex2) {
      return true; // Edge found
    }
    edge = edge->next;
  }

  return false; // Edge not found
}

Weight get_edge_weight(const Graph *graph, int source, int destination) {
  if (!is_valid_graph(graph) || !is_valid_vertex(graph, source) ||
      !is_valid_vertex(graph, destination)) {
    return EMPTY_EDGE;
  }

  Pointer edge = graph->adjacency_list[source];
  while (edge != NULL) {
    if (edge->destination == destination) {
      return edge->weight;
    }
    edge = edge->next;
  }

  return EMPTY_EDGE;
}

bool add_edge(Graph *graph, int source, int destination, Weight weight) {
  if (!is_valid_graph(graph) || !is_valid_vertex(graph, source) ||
      !is_valid_vertex(graph, destination)) {
    return false; // Invalid vertices
  }

  Pointer edge = (Pointer)calloc(1, sizeof(Edge));
  if (!edge) {
    fprintf(stderr, "Memory allocation failed.\n");
    return false;
  }
  edge->destination = destination;
  edge->weight = weight;

  Pointer prev = NULL;
  Pointer curr = graph->adjacency_list[source];

  // Find the correct position to insert the edge
  while (curr != NULL && curr->destination < destination) {
    prev = curr;
    curr = curr->next;
  }

  if (prev == NULL) {
    // Insert at the beginning of the list
    edge->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = edge;
  } else {
    // Insert in the middle or at the end of the list
    prev->next = edge;
    edge->next = curr;
  }

  // for an undirected graph
  Pointer reverse_edge = (Pointer)calloc(1, sizeof(Edge));
  if (!reverse_edge) {
    fprintf(stderr, "Memory allocation failed.\n");
    return false;
  }
  reverse_edge->destination = source;
  reverse_edge->weight = weight;

  prev = NULL;
  curr = graph->adjacency_list[destination];

  // Find the correct position to insert the reverse edge
  while (curr != NULL && curr->destination < source) {
    prev = curr;
    curr = curr->next;
  }

  if (prev == NULL) {
    // Insert at the beginning of the list
    reverse_edge->next = graph->adjacency_list[destination];
    graph->adjacency_list[destination] = reverse_edge;
  } else {
    // Insert in the middle or at the end of the list
    prev->next = reverse_edge;
    reverse_edge->next = curr;
  }

  return true;
}

bool remove_edge(Graph *graph, int source, int destination, Weight *weight) {
  if (!check_edge(graph, source, destination)) {
    return false;
  }

  Pointer prev = NULL;
  Pointer current = graph->adjacency_list[source];

  // Traverse the adjacency list of the source vertex
  while (current != NULL) {
    if (current->destination == destination) {
      // Found the edge, remove it
      if (weight != NULL) {
        *weight = current->weight; // Store the weight of the removed edge
      }

      if (prev == NULL) {
        graph->adjacency_list[source] =
            current->next; // Update the head of the adjacency list
      } else {
        prev->next = current->next;
      }

      free(current);
      return true;
    }

    prev = current;
    current = current->next;
  }

  return false; // Edge not found
}

void free_graph(Graph *graph) {
  if (graph == NULL) {
    return;
  }

  // Free the adjacency list
  for (int i = 0; i < graph->numVertices; i++) {
    Pointer current = graph->adjacency_list[i];
    while (current != NULL) {
      Pointer tmp = current;
      current = current->next;
      free(tmp);
    }
  }

  // Free the graph
  free(graph->adjacency_list);
}

void print_graph(const Graph *graph) {
  if (!is_valid_graph(graph)) {
    return;
  }

  int numVertices = graph->numVertices;

  for (int i = 0; i < numVertices; i++) {
    printf("Vertex %d:", i);

    Pointer current = graph->adjacency_list[i];
    while (current != NULL) {
      printf(" %d", current->destination);
      current = current->next;
    }

    printf("\n");
  }
}

int get_destination_vertex(const Graph *graph, int source, Pointer edge) {
  if (!is_valid_graph(graph) || !is_valid_vertex(graph, source) ||
      edge == NULL) {
    return EMPTY_EDGE;
  }

  return edge->destination;
}

Pointer get_vertex_ptr(const Graph *graph, int vertex) {
  if (!is_valid_graph(graph) || !is_valid_vertex(graph, vertex)) {
    return INVALID_VERTEX;
  }

  return graph->adjacency_list[vertex];
}
