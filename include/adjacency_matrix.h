#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include <stdbool.h>

#define MAX_VERTICES 100
#define EMPTY_EDGE -1
#define INVALID_VERTICE -1

typedef int Weight;
typedef struct Graph {
  int numVertices;
  int numEdges;
  Weight matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

/**
 * Initializes the adjacency matrix of the graph.
 *
 * @param graph The graph struct.
 * @param numVertices The number of vertices in the graph.
 * @return true if the matrix is successfully initialized, false otherwise.
 */
bool init_matrix(Graph *graph, int numVertices);

/**
 * Adds an edge with weight between two vertices in the graph.
 *
 * @param graph The graph struct.
 * @param vertex1 The index of the first vertex.
 * @param vertex2 The index of the second vertex.
 * @param weight The weight of the edge.
 * @return true if the edge is successfully added, false otherwise.
 */
bool add_edge(Graph *graph, int vertex1, int vertex2, Weight weight);

/**
 * Checks if there is an edge between two vertices in the graph.
 *
 * @param graph The graph struct.
 * @param vertex1 The index of the first vertex.
 * @param vertex2 The index of the second vertex.
 * @return true if there is an edge between the vertices, false otherwise.
 */
bool is_edge(Graph *graph, int vertex1, int vertex2);

/**
 * Checks if a given vertex index is valid in the graph.
 *
 * @param graph The graph struct.
 * @param vertex The index of the vertex.
 * @return true if the vertex index is valid, false otherwise.
 */
bool is_valid_vertex(Graph *graph, int vertex);

/**
 * Retrieves the weight of the edge between two vertices in the graph.
 *
 * @param graph The graph struct.
 * @param vertex1 The index of the first vertex.
 * @param vertex2 The index of the second vertex.
 * @return The weight of the edge if it exists, otherwise returns -1.
 */
Weight get_edge_weight(Graph *graph, int vertex1, int vertex2);

/**
 * Removes an edge between two vertices in the graph.
 *
 * @param graph The graph struct.
 * @param vertex1 The index of the first vertex.
 * @param vertex2 The index of the second vertex.
 * @param weight Pointer to the variable to store the weight of the removed
 * edge.
 * @return true if the edge is successfully removed, false otherwise.
 */
bool remove_edge(Graph *graph, int vertex1, int vertex2, Weight *weight);

/**
 * Checks if the list of adjacency vertices of a given vertex is null.
 *
 * @param graph The graph struct.
 * @param vertex The index of the vertex to check.
 * @return true if the list of adjacency vertices is null, false otherwise.
 *         Returns false if the vertex index is invalid.
 */
bool is_adjacency_list_null(Graph *graph, int vertex);

/**
 * Returns the next adjacent vertex to a given vertex.
 *
 * This function iterates through the vertices adjacent to the specified
 * vertex in the graph, starting from the current vertex adjacent to the
 * specified vertex. It returns the next adjacent vertex based on the
 * current vertex provided. If there are no more adjacent vertices, it
 * returns INVALID_VERTICE number.
 *
 * @param graph The graph struct.
 * @param vertex The index of the vertex to get the next adjacent vertex from.
 * @param current_vertex The index of the current adjacent vertex to start from.
 * @return The index of the next adjacent vertex, or -1 if there are no more
 *         adjacent vertices. Returns INVALID_VERTICE num if the vertex index is
 * invalid.
 */
int get_next_adjacent_vertex(Graph *graph, int vertex, int current_vertex);

/**
 * Frees the memory allocated for the adjacency matrix graph.
 *
 * This function frees the memory allocated for the adjacency matrix
 * graph and deallocates any dynamically allocated resources.
 *
 * @param graph The graph struct to be freed.
 */
void free_graph(Graph *graph);

#endif
