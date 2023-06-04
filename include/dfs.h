#ifndef DFS_H
#define DFS_H

#include "adjacency_list.h"

typedef enum {
  WHITE, // Initial color for vertices
  GRAY,  // Color for vertices being visited
  BLACK  // Color for vertices that have been visited
} Color;

/**
 * Performs a Depth-First Search (DFS) traversal on the given graph.
 *
 * @param graph The graph to perform the DFS traversal on.
 */
void DFS(const Graph *graph);

/**
 * Performs a Depth-First Search (DFS) visit on the specified vertex.
 *
 * @param vertex The vertex to visit.
 * @param graph The graph containing the vertex.
 * @param time Pointer to the time counter.
 * @param color Array representing the color of each vertex.
 * @param discoveryTime Array to store the discovery time of each vertex.
 * @param finishingTime Array to store the finishing time of each vertex.
 * @param predecessor Array to store the predecessor of each vertex.
 */
void DFSVisit(int vertex, const Graph *graph, int *time, Color *color,
              int *discoveryTime, int *finishingTime, int *predecessor);

#endif
