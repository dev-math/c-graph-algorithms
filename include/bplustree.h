#ifndef B_TREEPLUS_H
#define B_TREEPLUS_H

#include <stdbool.h>
#include <stdio.h>

#define T 3 // minimum degree of the b+ tree
#define MAX_KEYS (2 * T - 1)
#define MAX_CHILDREN (2 * T)

typedef struct BPlusTreeNode {
  bool isLeaf;
  int *keys;
  int keysSize;
  struct BPlusTreeNode **children;
  struct BPlusTreeNode *next;
} BPlusTreeNode;

BPlusTreeNode *create_bplustree();
BPlusTreeNode *search_bplustree_node(BPlusTreeNode *node, int key);
void delete_bplustree_node(BPlusTreeNode *root, int key);
bool insert_bplustree_node(BPlusTreeNode **root, int key);
void print_bplustree(BPlusTreeNode *tree, int level, FILE *outputFile);
void free_bplustree(BPlusTreeNode *tree);

#endif
