#ifndef DIJKSTRAS_H 
#define DIJKSTRAS_H 

#ifdef USE_MATRIX_IMPLEMENTATION
#include "adjacency_matrix.h"
#elif USE_LIST_IMPLEMENTATION
#include "adjacency_list.h"
#endif

#define INFINITY 999999
#define VISITED true
#define UNVISITED false

void dijkstra(const Graph *graph, int source);

#endif
