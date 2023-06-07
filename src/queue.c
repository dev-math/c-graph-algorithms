#include "../include/queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init_queue(Queue *queue) {
  queue->front = NULL;
  queue->rear = NULL;
}

bool enqueue(Queue *queue, int data) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    return false;
  }

  newNode->data = data;
  newNode->next = NULL;

  if (queue->rear == NULL) {
    queue->front = newNode;
    queue->rear = newNode;
  } else {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }

  return true;
}

int dequeue(Queue *queue) {
  if (is_empty(queue)) {
    return false; // Queue is empty
  }

  QueueNode *temp = queue->front;
  int tmpData = temp->data;
  queue->front = queue->front->next;

  if (queue->front == NULL) {
    queue->rear = NULL; // The queue is now empty
  }

  free(temp);
  return tmpData;
}

bool is_empty(const Queue *queue) { return (queue->front == NULL); }

void free_queue(Queue *queue) {
  while (!is_empty(queue)) {
    dequeue(queue);
  }
}
