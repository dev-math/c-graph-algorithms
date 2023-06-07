#include "../include/heap.h"
#include <stdio.h>
#include <stdlib.h>

bool init_heap(Heap *heap, int size) {
  heap->array = (HeapNode *)malloc(size * sizeof(HeapNode));
  if (heap->array == NULL) {
    fprintf(stderr, "Error: Failed to allocate memory for the heap array.\n");
    return false;
  }

  heap->size = size;
  return true;
}

bool is_heap_empty(const Heap *heap) { return (heap->size == 0); }

int extract_min(Heap *heap) {
  HeapNode minNode = heap->array[0];
  heap->array[0] = heap->array[heap->size - 1];
  heap->size--;

  int i = 0;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int smallest = i;

  while (left < heap->size) {
    if (heap->array[left].key < heap->array[smallest].key)
      smallest = left;

    if (right < heap->size &&
        heap->array[right].key < heap->array[smallest].key)
      smallest = right;

    if (smallest != i) {
      HeapNode temp = heap->array[i];
      heap->array[i] = heap->array[smallest];
      heap->array[smallest] = temp;
      i = smallest;
      left = 2 * i + 1;
      right = 2 * i + 2;
    } else {
      break;
    }
  }

  return minNode.vertex;
}

bool decrease_key(Heap *heap, int vertex, Weight key) {
  int i = 0;
  for (i = 0; i < heap->size; i++) {
    if (heap->array[i].vertex == vertex)
      break;
  }

  if (i >= heap->size) {
    fprintf(stderr, "Error: Vertex not found in the heap.\n");
    return false;
  }

  heap->array[i].key = key;

  while (i > 0 && heap->array[(i - 1) / 2].key > heap->array[i].key) {
    HeapNode temp = heap->array[i];
    heap->array[i] = heap->array[(i - 1) / 2];
    heap->array[(i - 1) / 2] = temp;
    i = (i - 1) / 2;
  }

  return true;
}

void free_heap(Heap *heap) { free(heap->array); }
