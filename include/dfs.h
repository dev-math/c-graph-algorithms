#ifndef DFS_H
#define DFS_H

#ifdef USE_MATRIX_IMPLEMENTATION
#include "adjacency_matrix.h"
#elif USE_LIST_IMPLEMENTATION
#include "adjacency_list.h"
#endif

#define VISITED true
#define UNVISITED false

void dfs_recursive(const Graph *graph, int initialVertex,
                   Pointer initialVertexPtr, bool *visited);
void dfs(const Graph *graph, int initialVertex);

#endif
