#ifndef PRIM_H
#define PRIM_H

#ifdef USE_MATRIX_IMPLEMENTATION
#include "../include/adjacency_matrix.h"
#elif USE_LIST_IMPLEMENTATION
#include "../include/adjacency_list.h"
#endif

#define INFINITY_POS 999999
#define INFINITY_NEG (-999999)
#define VISITED true
#define UNVISITED false

Graph mst_prim(Graph *graph, int initialVertex);

#endif
