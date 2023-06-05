#include "../include/bfs.h"
#include "../include/queue.h"

#include <stdio.h>
#include <stdlib.h>

#define VISITED true
#define UNVISITED false

void bfs(const Graph *graph, int initialVertex) {
  bool visited[graph->numVertices];
  for (int i = 0; i < graph->numVertices; i++) {
    visited[i] = UNVISITED;
  }

  Queue queue;
  init_queue(&queue);

  enqueue(&queue, initialVertex);

  while (!is_empty(&queue)) {
    int vertex = dequeue(&queue);
    if (visited[vertex] == UNVISITED) {
      printf("Visiting %d\n", vertex); // visit vertex
      visited[vertex] = VISITED;

      Pointer adjacentVertex =
          get_next_adjacent_vertex(graph, vertex, INVALID_VERTEX);

      while (adjacentVertex != INVALID_VERTEX) {
        int adjacentIndex =
            get_destination_vertex(graph, vertex, adjacentVertex);
        if (visited[adjacentIndex] == UNVISITED) {
          enqueue(&queue, adjacentIndex);
        }

        adjacentVertex =
            get_next_adjacent_vertex(graph, vertex, adjacentVertex);
      }
    }
  }
}
