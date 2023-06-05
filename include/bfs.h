#ifndef BFS_H
#define BFS_H

#ifdef USE_MATRIX_IMPLEMENTATION
#include "adjacency_matrix.h"
#elif USE_LIST_IMPLEMENTATION
#include "adjacency_list.h"
#endif

#define VISITED true
#define UNVISITED false

void bfs(const Graph *graph, int initialVertex);

#endif
