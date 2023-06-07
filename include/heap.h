#ifndef HEAP_H
#define HEAP_H

#ifdef USE_MATRIX_IMPLEMENTATION
#include "adjacency_matrix.h"
#elif USE_LIST_IMPLEMENTATION
#include "adjacency_list.h"
#endif

#include <stdbool.h>

typedef struct {
  int vertex;
  Weight key;
} HeapNode;

typedef struct {
  HeapNode *array;
  int size;
} Heap;

/**
 * Initializes the heap with the given size.
 *
 * @param heap  Pointer to the heap struct.
 * @param size  The size of the heap.
 * @return      True if the heap is initialized successfully, false otherwise.
 */
bool init_heap(Heap *heap, int size);

/**
 * Checks if the heap is empty.
 *
 * @param heap  Pointer to the heap struct.
 * @return      True if the heap is empty, false otherwise.
 */
bool is_heap_empty(const Heap *heap);

/**
 * Extracts the minimum element from the heap.
 *
 * @param heap      Pointer to the heap struct.
 * @return          The minimum element extracted
 */
int extract_min(Heap *heap);

/**
 * Decreases the key value of a vertex in the heap.
 *
 * @param heap      Pointer to the heap struct.
 * @param vertex    The vertex whose key value needs to be decreased.
 * @param key       The new key value for the vertex.
 * @return          True if the key value is decreased successfully, false
 * otherwise.
 */
bool decrease_key(Heap *heap, int vertex, Weight key);

/**
 * @param   heap    Pointer to the Heap.
 * @return          None.
 */
void free_heap(Heap *heap);

#endif
