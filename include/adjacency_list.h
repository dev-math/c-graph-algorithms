#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <stdbool.h>

#define INVALID_VERTICE NULL
#define EMPTY_EDGE -1

typedef double Weight;

typedef struct Edge {
  int destination;
  Weight weight;
  struct Edge *next;
} Edge;

typedef Edge *Pointer;

typedef struct Graph {
  int numVertices;
  Pointer *adjacency_list;
} Graph;

/**
 * Initialize a graph with the specified number of vertices.
 *
 * @param graph         Pointer to the graph struct to be initialized.
 * @param numVertices   Number of vertices in the graph.
 * @return              True if the graph is initialized successfully, false
 * otherwise.
 */
bool init_graph(Graph *graph, int numVertices);

/**
 * Checks if a given vertex index is valid in the graph.
 *
 * @param graph         Pointer to the graph struct.
 * @param vertex        The index of the vertex.
 * @return              True if the vertex index is valid, false otherwise.
 */
bool is_valid_vertex(const Graph *graph, int vertex);

/**
 * Check if the adjacency list of a vertex is null.
 *
 * @param graph         Pointer to the graph struct.
 * @param vertex        Vertex to check the adjacency list for.
 * @return              True if the adjacency list is null, false otherwise.
 */
bool is_adjacency_list_null(const Graph *graph, int vertex);

/**
 * Returns the next adjacent vertex to the given vertex
 *
 * @param graph         The graph containing the adjacency list.
 * @param               current_vertex The current vertex representing the
 * current position in the adjacency list.
 * @return              Pointer to the next adjacent vertex if found, or
 * INVALID_VERTICE if the current vertex is invalid or there are no more
 * adjacent vertices.
 */
Pointer get_adjacent_vertex(const Graph *graph, Pointer current_vertex);

/**
 * Checks if there is an edge between two given vertices in the graph.
 *
 * @param graph The graph containing the adjacency list.
 * @param vertex1 The first vertex.
 * @param vertex2 The second vertex.
 * @return True if there is an edge between the vertices, false otherwise.
 */
bool check_edge(const Graph *graph, int vertex1, int vertex2);

/**
 * Get the weight of an edge between two vertices in the graph.
 *
 * @param graph         Pointer to the graph struct.
 * @param source        Source vertex of the edge.
 * @param destination   Destination vertex of the edge.
 * @return              Weight of the edge if it exists, or EMPTY_EDGE if the
 * edge doesn't exist.
 */
Weight get_edge_weight(const Graph *graph, int source, int destination);

/**
 * Add an edge between two vertices in the graph.
 *
 * @param graph         Pointer to the graph struct.
 * @param source        Source vertex of the edge.
 * @param destination   Destination vertex of the edge.
 * @param weight        Weight of the edge.
 * @return              True if the edge is added successfully, false otherwise.
 */
bool add_edge(Graph *graph, int source, int destination, Weight weight);

/**
 * Remove an edge between two vertices in the graph.
 *
 * @param graph         Pointer to the graph struct.
 * @param source        Source vertex of the edge.
 * @param destination   Destination vertex of the edge.
 * @param weight        Pointer to an integer to store the removed edge weight
 * @return              True if the edge is removed successfully, false
 * otherwise.
 */
bool remove_edge(Graph *graph, int source, int destination, Weight *weight);

/**
 * Free the memory allocated for the graph.
 *
 * @param graph         Pointer to the graph struct to be freed.
 */
void free_graph(Graph *graph);

/**
 * Prints the graph by displaying each vertex and its adjacent vertices.
 *
 * @param graph The graph to be printed.
 */
void print_graph(const Graph *graph);

#endif
