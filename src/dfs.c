#include "../include/dfs.h"
#include <stdio.h>
#include <stdlib.h>

void DFSVisit(int vertex, const Graph *graph, int *time, Color *color,
              int *discoveryTime, int *finishingTime, int *predecessor) {

  color[vertex] = GRAY;              // Mark the current vertex as being visited
  discoveryTime[vertex] = (*time)++; // Increment the discovery time

  // Traverse all adjacent vertices
  Edge *adjacentVertex =
      get_next_adjacent_vertex(graph, graph->adjacency_list[vertex]);
  while (adjacentVertex != INVALID_VERTICE) {
    int adjacent = adjacentVertex->destination;
    // If the adjacent vertex is not visited, set its predecessor and
    // recursively visit it
    if (color[adjacent] == WHITE) {
      predecessor[adjacent] = vertex;
      DFSVisit(adjacent, graph, time, color, discoveryTime, finishingTime,
               predecessor);
    }

    adjacentVertex = get_next_adjacent_vertex(graph, adjacentVertex);
  }

  finishingTime[vertex] = (*time)++; // Increment the finishing time
  color[vertex] = BLACK;             // Mark the current vertex as visited
  printf("vertex %d\n", vertex);
}

void DFS(const Graph *graph) {
  Color *color = (Color *)malloc(graph->numVertices * sizeof(Color));
  int *discoveryTime = malloc(graph->numVertices * sizeof(int)); // d[v]
  int *finishingTime = malloc(graph->numVertices * sizeof(int)); // t[v]
  int *predecessor = malloc(graph->numVertices * sizeof(int));

  // Check if memory allocation was successful
  if (!(color && discoveryTime && finishingTime && predecessor)) {
    fprintf(stderr, "Memory allocation failed.\n");
    free(color);
    free(discoveryTime);
    free(finishingTime);
    free(predecessor);
    return;
  }

  // Initialize time counter
  int time = 0;

  // Initialize the state of each vertex
  for (int v = 0; v < graph->numVertices; v++) {
    color[v] = WHITE;
    discoveryTime[v] = 0;
    finishingTime[v] = 0;
    predecessor[v] = -1;
  }

  // Traverse all vertices
  for (int v = 0; v < graph->numVertices; v++) {
    if (color[v] == WHITE) { // If a vertex is not visited, visit it
      DFSVisit(v, graph, &time, color, discoveryTime, finishingTime,
               predecessor);
    }
  }

  free(color);
  free(discoveryTime);
  free(finishingTime);
  free(predecessor);
}
