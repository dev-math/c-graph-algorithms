#ifndef QUEUE_H
#define QUEUE_H

#ifdef USE_MATRIX_IMPLEMENTATION
#include "adjacency_matrix.h"
#elif USE_LIST_IMPLEMENTATION
#include "adjacency_list.h"
#endif

#include <stdbool.h>

typedef struct QueueNode {
  int data;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue {
  QueueNode *front;
  QueueNode *rear;
} Queue;

/**
 * @param   queue   Pointer to the queue struct to be initialized.
 * @return          None.
 */
void init_queue(Queue *queue);

/**
 * @param   queue   Pointer to the queue.
 * @param   data    The data to be added to the queue.
 * @return          None.
 */
bool enqueue(Queue *queue, int data);

/**
 * @param   queue   Pointer to the queue.
 * @return          The element removed from the queue.
 */
int dequeue(Queue *queue);

/**
 * @param   queue   Pointer to the queue.
 * @return          True if the queue is empty, false otherwise.
 */
bool is_empty(const Queue *queue);

/**
 * @param   queue   Pointer to the queue.
 * @return          None.
 */
bool free_queue(Queue *queue);

#endif
