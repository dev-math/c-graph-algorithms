#include "../include/adjacency_matrix.h"
#include <stdbool.h>
#include <stdio.h>

void print_test_result(bool success) {
  if (success) {
    printf("✅ ");
  } else {
    printf("❌ ");
  }
}

void test_adjacency_matrix() {
  Graph graph;
  int num_vertices = 5;

  // Initialize the adjacency matrix
  if (!init_graph(&graph, num_vertices)) {
    fprintf(stderr, "Failed to initialize the adjacency matrix.\n");
    return;
  }

  // Add some edges
  add_edge(&graph, 0, 1, 10);
  add_edge(&graph, 0, 3, 5);
  add_edge(&graph, 1, 2, 3);
  add_edge(&graph, 2, 4, 7);
  add_edge(&graph, 3, 4, 2);

  // Check if edges exist
  bool is_edge_01 = check_edge(&graph, 0, 1);
  print_test_result(is_edge_01 == true);
  printf("Edge between vertex 0 and vertex 1\n");

  bool is_edge_13 = check_edge(&graph, 1, 3);
  print_test_result(is_edge_13 == false);
  printf("No edge between vertex 1 and vertex 3\n");

  bool is_edge_23 = check_edge(&graph, 2, 3);
  print_test_result(is_edge_23 == false);
  printf("No edge between vertex 2 and vertex 3\n");

  // Get edge weight
  Weight weight_03 = get_edge_weight(&graph, 0, 3);
  print_test_result(weight_03 == 5);
  printf("Weight of the edge between vertex 0 and vertex 3: %.2f\n", weight_03);

  // Remove an edge
  Weight removed_weight;
  bool is_edge_removed = remove_edge(&graph, 1, 2, &removed_weight);
  print_test_result(is_edge_removed == true);
  printf("Removed edge 1->2 weight: %.2f\n", removed_weight);

  // Check if adjacency list is null
  bool is_adj_list_null_0 = is_adjacency_list_null(&graph, 0);
  print_test_result(is_adj_list_null_0 == false);
  printf("Adjacency list of vertex 0 is not null\n");

  bool is_adj_list_null_2 = is_adjacency_list_null(&graph, 2);
  print_test_result(is_adj_list_null_2 == false);
  printf("Adjacency list of vertex 2 is not null\n");

  // Print the graph
  printf("\nGraph:\n");
  print_graph(&graph);

  // Free the graph memory
  free_graph(&graph);
}

int main() {
  test_adjacency_matrix();

  return 0;
}
