#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include <stdbool.h>

#define MAX_VERTICES 100
#define EMPTY_EDGE -1
#define INVALID_VERTEX -1

typedef double Weight;
typedef int Pointer;

typedef struct Graph {
  int numVertices;
  int numEdges;
  Weight matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

/**
 * @param graph         Pointer to the graph struct to be initialized.
 * @param numVertices   Number of vertices in the graph.
 * @return              True if the graph is initialized successfully, false
 * otherwise.
 */
bool init_graph(Graph *graph, int numVertices);

/**
 * @param graph     Pointer to the graph struct to be checked.
 * @return          Returns true if the graph is valid, i.e., it has been
 * initialized, and false otherwise.
 */
bool is_valid_graph(const Graph *graph);

/**
 * @param graph         Pointer to the graph struct.
 * @param vertex        The index of the vertex.
 * @return              True if the vertex index is valid, false otherwise.
 */
bool is_valid_vertex(const Graph *graph, int vertex);

/**
 * @param graph         Pointer to the graph struct.
 * @param vertex        Vertex to check the adjacency list for.
 * @return              True if the adjacency list is null, false otherwise.
 */
bool is_adjacency_list_null(const Graph *graph, int vertex);

/**
 * @param graph           The graph struct.
 * @param vertex          The index of the vertex to get the next adjacent
 * vertex from.
 * @param current_vertex  The index of the current adjacent vertex to start
 * from.
 * @return                The index of the next adjacent vertex, or
 * INVALID_VERTEX if there are no more adjacent vertices. Returns
 * INVALID_VERTEX if the vertex index is invalid.
 */
Pointer get_next_adjacent_vertex(const Graph *graph, int vertex,
                                 Pointer current_vertex);

/**
 * @param graph         The graph containing the adjacency list.
 * @param vertex1       The first vertex.
 * @param vertex2       The second vertex.
 * @return              True if there is an edge between the vertices, false
 * otherwise.
 */
bool check_edge(const Graph *graph, int vertex1, int vertex2);

/**
 * @param graph         Pointer to the graph struct.
 * @param vertex1       Source vertex of the edge.
 * @param vertex2       Destination vertex of the edge.
 * @return              Weight of the edge if it exists, or EMPTY_EDGE if the
 * edge doesn't exist.
 */
Weight get_edge_weight(const Graph *graph, int vertex1, int vertex2);

/**
 * @param graph         Pointer to the graph struct.
 * @param source        Source vertex of the edge.
 * @param destination   Destination vertex of the edge.
 * @param weight        Weight of the edge.
 * @return              True if the edge is added successfully, false otherwise.
 */
bool add_edge(Graph *graph, int source, int destination, Weight weight);

/**
 * @param graph         Pointer to the graph struct.
 * @param source        Source vertex of the edge.
 * @param destination   Destination vertex of the edge.
 * @param weight        Pointer to a Weight to store the removed edge weight
 * @return              True if the edge is removed successfully, false
 * otherwise.
 */
bool remove_edge(Graph *graph, int source, int destination, Weight *weight);

/**
 * @param graph         Pointer to the graph struct to be freed.
 */
void free_graph(Graph *graph);

/**
 * Prints the graph by displaying each vertex and its adjacent vertices.
 *
 * @param graph The graph to be printed.
 */
void print_graph(const Graph *graph);

/**
 * @param graph       Pointer to the graph struct.
 * @param source      Source vertex of the edge.
 * @param edge        Pointer to the edge
 * @return            The destination vertex of the edge, or INVALID_VERTEX if
 * the edge doesn't exist.
 */
int get_destination_vertex(const Graph *graph, int source, Pointer edge);

/**
 * @param graph       Pointer to the graph struct.
 * @param vertex      Vertex to convert.
 * @return            The Pointer of the vertex, or INVALID_VERTEX if the vertex
 * doesn't exist
 */
Pointer get_vertex_ptr(const Graph *graph, int vertex);

#endif
