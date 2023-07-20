#include "../include/bplustree.h"
#include <stdio.h>

void print_test_result(bool success) {
  if (success) {
    printf("✅ ");
  } else {
    printf("❌ ");
  }
}

void test_b_tree() {
  BPlusTreeNode *root = create_bplustree();
  print_bplustree(root, 0, stdout);
  printf("\n");
  insert_bplustree_node(&root, 30);
  print_bplustree(root, 0, stdout);
  printf("\n");
  insert_bplustree_node(&root, 9);
  insert_bplustree_node(&root, 5);
  insert_bplustree_node(&root, 8);
  insert_bplustree_node(&root, 17);
  insert_bplustree_node(&root, 26);
  print_bplustree(root, 0, stdout);
  printf("\n");
  insert_bplustree_node(&root, 41);
  insert_bplustree_node(&root, 2);
  insert_bplustree_node(&root, 3);
  insert_bplustree_node(&root, 51);
  insert_bplustree_node(&root, 90);
  print_bplustree(root, 0, stdout);
  printf("\n");
  insert_bplustree_node(&root, 4);
  insert_bplustree_node(&root, 11);
  insert_bplustree_node(&root, 12);
  insert_bplustree_node(&root, 13);
  insert_bplustree_node(&root, 14);
  insert_bplustree_node(&root, 15);
  insert_bplustree_node(&root, 16);
  print_bplustree(root, 0, stdout);
  printf("\n");
  delete_bplustree_node(root, 30);
  print_bplustree(root, 0, stdout);
  printf("\n");
  delete_bplustree_node(root, 41);
  delete_bplustree_node(root, 11);
  print_bplustree(root, 0, stdout);
  printf("\n");
  delete_bplustree_node(root, 14);
  print_bplustree(root, 0, stdout);
  printf("\n");
  delete_bplustree_node(root, 15);
  print_bplustree(root, 0, stdout);
  printf("\n");
  delete_bplustree_node(root, 13);
  print_bplustree(root, 0, stdout);
  printf("\n");
  delete_bplustree_node(root, 2);
  print_bplustree(root, 0, stdout);
  printf("\n");
  delete_bplustree_node(root, 16);
  print_bplustree(root, 0, stdout);
  printf("\n");
  delete_bplustree_node(root, 26);
  delete_bplustree_node(root, 12);
  print_bplustree(root, 0, stdout);
  printf("\n");
}

int main() {
  test_b_tree();

  return 0;
}
