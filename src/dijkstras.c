#include "../include/dijkstras.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void dijkstra(const Graph *graph, int source) {
  int numVertices = graph->numVertices;
  bool visited[numVertices];
  int distances[numVertices];

  // Initialize visited and distances arrays
  for (int i = 0; i < numVertices; i++) {
    visited[i] = UNVISITED;
    distances[i] = INFINITY;
  }

  distances[source] = 0;

  for (int i = 0; i < numVertices - 1; i++) {
    // Find the vertex with the minimum distance
    int minDistance = INFINITY;
    int minVertex;

    for (int v = 0; v < numVertices; v++) {
      if (!visited[v] && distances[v] <= minDistance) {
        minDistance = distances[v];
        minVertex = v;
      }
    }

    visited[minVertex] = VISITED;

    // Update distances of the adjacent vertices
    Pointer edge = get_next_adjacent_vertex(graph, minVertex, INVALID_VERTEX);
    while (edge != INVALID_VERTEX) {
      int destination = get_destination_vertex(graph, minVertex, edge);
      Weight weight = get_edge_weight(graph, minVertex, destination);

      if (!visited[destination] && distances[minVertex] != INFINITY &&
          distances[minVertex] + weight < distances[destination]) {
        distances[destination] = distances[minVertex] + weight;
      }

      edge = get_next_adjacent_vertex(graph, minVertex, edge);
    }
  }

  // Print the shortest distances from the source vertex
  printf("Shortest distances from vertex %d:\n", source);
  for (int i = 0; i < numVertices; i++) {
    printf("Vertex %d: ", i);
    if (distances[i] == INFINITY) {
      printf("Not reachable\n");
    } else {
      printf("%d\n", distances[i]);
    }
  }
}
