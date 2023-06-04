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

bool is_valid_vertex(const Graph *graph, int vertex) {
  return (vertex >= 0 && vertex < graph->numVertices);
}

bool is_adjacency_list_null(const Graph *graph, int vertex) {
  if (!is_valid_vertex(graph, vertex)) {
    return true;
  }
  return (graph->adjacency_list[vertex] == NULL);
}

Pointer get_next_adjacent_vertex(const Graph *graph, Pointer current_vertex) {
  if (!current_vertex) {
    return INVALID_VERTICE;
  }

  return (current_vertex->next);
}

bool check_edge(const Graph *graph, int vertex1, int vertex2) {
  if (!is_valid_vertex(graph, vertex1) || !is_valid_vertex(graph, vertex2)) {
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
  if (!is_valid_vertex(graph, source) || !is_valid_vertex(graph, destination)) {
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
  if (!is_valid_vertex(graph, source) || !is_valid_vertex(graph, destination)) {
    return false; // Invalid vertices
  }

  Pointer edge = (Pointer)calloc(1, sizeof(Edge));
  if (!edge) {
    fprintf(stderr, "Memory allocation failed.\n");
    return false;
  }
  edge->destination = destination;
  edge->weight = weight;
  edge->next = graph->adjacency_list[source];
  graph->adjacency_list[source] = edge;
  // graph->numEdges++; //TODO: check if I need this prop
  return true;
}

bool remove_edge(Graph *graph, int source, int destination, Weight *weight) {
  if (!is_valid_vertex(graph, source) || !is_valid_vertex(graph, destination)) {
    return false; // Invalid vertices
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
  if (graph == NULL) {
    return;
  }

  printf("Graph:\n");
  for (int i = 0; i < graph->numVertices; i++) {
    printf("Vertex %d:", i);

    Pointer current = graph->adjacency_list[i];
    while (current != NULL) {
      printf(" %d", current->destination);
      current = current->next;
    }

    printf("\n");
  }
}
