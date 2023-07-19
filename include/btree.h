#ifndef B_TREE_H
#define B_TREE_H

#include <stdbool.h>

#define T 3 // minimum degree of the B-Tree
#define MAX_KEYS (2 * T - 1)
#define MAX_CHILDREN (2 * T)

typedef struct BTreeNode {
  bool isLeaf;
  int *keys;
  int keysSize;
  struct BTreeNode **children;
} BTreeNode;

BTreeNode *create_btree();
BTreeNode *search_btree_node(BTreeNode *node, int key);
void delete_btree_node(BTreeNode **root, BTreeNode *x, int k);
bool insert_btree_node(BTreeNode **root, int key);
void print_btree(BTreeNode *tree, int level);
void free_btree(BTreeNode *tree);

#endif
