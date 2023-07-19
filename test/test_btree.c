#include "../include/btree.h"
#include <stdio.h>

void print_test_result(bool success) {
  if (success) {
    printf("✅ ");
  } else {
    printf("❌ ");
  }
}

void test_b_tree() {
  BTreeNode *root = create_btree();
  int key;

  printf("Initial B-tree:\n");
  print_btree(root, 0);
  printf("\n");

  // Insert some keys
  insert_btree_node(&root, 10);
  insert_btree_node(&root, 20);
  insert_btree_node(&root, 5);
  insert_btree_node(&root, 15);
  insert_btree_node(&root, 25);

  printf("After insertion:\n");
  print_btree(root, 0);
  printf("\n");

  // Search for keys
  key = 15;
  bool is_key_found = search_btree_node(root, key);
  printf("Search for key %d: ", key);
  print_test_result(is_key_found);
  printf("\n");

  key = 30;
  is_key_found = !search_btree_node(root, key);
  printf("Search for key %d: ", key);
  print_test_result(is_key_found);
  printf("\n");

  // Delete keys
  key = 5;
  delete_btree_node(&root, root, key);

  key = 20;
  delete_btree_node(&root, root, key);

  printf("After deletion:\n");
  print_btree(root, 0);
  printf("\n");

  // Free the B-tree
  free_btree(root);
}

int main() {
  test_b_tree();

  return 0;
}
