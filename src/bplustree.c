#include "../include/bplustree.h"
#include <stdio.h>
#include <stdlib.h>

BPlusTreeNode *create_bplustree_node() {
  BPlusTreeNode *ptr = (BPlusTreeNode *)malloc(sizeof(BPlusTreeNode));
  if (ptr == NULL) {
    fprintf(stderr, "Error: Could not allocate memory!\n");
    return NULL;
  }

  ptr->keys = (int *)malloc(sizeof(int) * MAX_KEYS);
  ptr->children =
      (BPlusTreeNode **)malloc(sizeof(BPlusTreeNode *) * MAX_CHILDREN);
  if (!ptr->keys || !ptr->children) {
    free(ptr->keys);
    free(ptr->children);
    free(ptr);
    return NULL;
  }

  ptr->isLeaf = true;
  ptr->keysSize = 0;
  ptr->next = NULL;

  for (int i = 0; i < MAX_CHILDREN; i++) {
    ptr->children[i] = NULL;
  }

  return ptr;
}

BPlusTreeNode *create_bplustree() { return create_bplustree_node(); }

BPlusTreeNode *search(BPlusTreeNode *ptr, int key) {
  if (!ptr) {
    return NULL;
  }

  int i = 0;

  while ((i <= ptr->keysSize) && (key > ptr->keys[i])) {
    i++;
  }

  if ((i <= ptr->keysSize) && (ptr->isLeaf) && (key == ptr->keys[i])) {
    return ptr;
  }

  if (ptr->isLeaf) {
    return NULL;
  }

  if (ptr->keys[i] == key) {
    i++;
  }

  return search(ptr->children[i], key);
}

BPlusTreeNode *split_node(BPlusTreeNode *nonFullNode, int index,
                          BPlusTreeNode *fullChild) {
  BPlusTreeNode *newChild = create_bplustree_node();
  if (!newChild) {
    return NULL;
  }
  newChild->isLeaf = fullChild->isLeaf;

  int median = T - 1;

  if (!fullChild->isLeaf) {
    newChild->keysSize = median;

    for (int j = 0; j < median; j++) {
      newChild->keys[j] = fullChild->keys[j + T];
    }

    for (int j = 0; j < T; j++) {
      newChild->children[j] = fullChild->children[j + T];
      fullChild->children[j + T] = NULL;
    }
  } else {
    newChild->keysSize = T;

    for (int j = 0; j < T; j++) {
      newChild->keys[j] = fullChild->keys[j + median];
    }

    fullChild->next = newChild;
  }

  fullChild->keysSize = median;

  for (int j = nonFullNode->keysSize; j >= index; j--) {
    nonFullNode->children[j + 1] = nonFullNode->children[j];
  }

  nonFullNode->children[index] = newChild;
  for (int j = nonFullNode->keysSize; j >= index; j--) {
    nonFullNode->keys[j] = nonFullNode->keys[j - 1];
  }

  nonFullNode->keys[index - 1] = fullChild->keys[median];
  nonFullNode->keysSize++;

  return nonFullNode;
}

BPlusTreeNode *split_child(BPlusTreeNode *parent, int index) {
  BPlusTreeNode *child = parent->children[index]; // full child

  BPlusTreeNode *newChild = create_bplustree_node();
  if (!newChild) {
    return NULL;
  }
  newChild->isLeaf = child->isLeaf;
  parent->children[index + 1] = newChild;

  // insert the median of the full child into parent
  int median = T - 1;
  parent->keys[index] = child->keys[median];
  parent->keysSize++;

  // split the full child keys with the new child
  // the new_child will take keys from median + 1 onwards
  newChild->keysSize = median;
  child->keysSize = median;
  for (int i = 0; i < median; i++) {
    newChild->keys[i] = child->keys[i + T];
  }

  if (!newChild->isLeaf) {
    // new_child will take children from index T onwards
    // child take until T
    for (int i = 0; i < median + 1; i++) {
      newChild->children[i] = child->children[i + T];
      child->children[i + T] = NULL;
    }
  }

  return newChild;
}

BPlusTreeNode *insert_into_non_full(BPlusTreeNode *node, int key) {
  int i = node->keysSize - 1;

  if (node->isLeaf) {
    while (i >= 0 && (key < node->keys[i])) {
      node->keys[i + 1] = node->keys[i];
      i--;
    }

    node->keys[i + 1] = key;
    node->keysSize++;

    return node;
  }

  while (i >= 0 && (key < node->keys[i])) {
    i--;
  }
  i++;

  if (node->children[i]->keysSize == MAX_KEYS) {
    node = split_node(node, i + 1, node->children[i]);

    if (key > node->keys[i]) {
      i++;
    }
  }

  node->children[i] = insert_into_non_full(node->children[i], key);
  return node;
}

bool insert_bplustree_node(BPlusTreeNode **root, int key) {
  if (search(*root, key)) {
    return false;
  }

  if (!*root) {
    *root = create_bplustree_node();
    if (!*root) {
      return false;
    }

    (*root)->keys[0] = key;
    (*root)->keysSize = 1;
    return true;
  }

  bool isRootFull = (*root)->keysSize == MAX_KEYS;
  if (isRootFull) {
    BPlusTreeNode *newRoot = create_bplustree_node();
    if (!newRoot) {
      return false;
    }

    newRoot->isLeaf = false;
    newRoot->children[0] = *root;
    newRoot = split_node(newRoot, 1, *root);
    newRoot = insert_into_non_full(newRoot, key);
    *root = newRoot;
    return true;
  }

  *root = insert_into_non_full(*root, key);
  return true;
}

void print_bplustree(BPlusTreeNode *ptr, int level, FILE *outputFile) {
  if (!ptr) {
    return;
  }

  if (ptr->keysSize == 0) {
    fprintf(outputFile, "Vazia");
    return;
  }

  int i;
  fprintf(outputFile, "(");
  for (i = 0; i <= ptr->keysSize - 1; i++) {
    print_bplustree(ptr->children[i], level + 1, outputFile);

    if (i != 0 && (i == ptr->keysSize - 1 || i != ptr->keysSize)) {
      fprintf(outputFile, " ");
    } else if (i <= level && !ptr->isLeaf) {
      fprintf(outputFile, " ");
    }

    fprintf(outputFile, "%d", ptr->keys[i]);

    if (!ptr->isLeaf) {
      fprintf(outputFile, " ");
    }
  }
  print_bplustree(ptr->children[i], level + 1, outputFile);
  fprintf(outputFile, ")");
}

void free_bplustree(BPlusTreeNode *node) {
  if (node) {
    if (!node->isLeaf) {
      for (int i = 0; i <= node->keysSize; i++) {
        free_bplustree(node->children[i]);
      }
      free(node->children);
    }
    free(node->keys);
    free(node);
  }
}

void delete_from_leaf(BPlusTreeNode *root, int index) {
  for (int i = index + 1; i < root->keysSize; i++) {
    root->keys[i - 1] = root->keys[i];
  }
  root->keysSize--;
}

void delete_from_non_leaf(BPlusTreeNode *root, int index);

void borrow_prev_child(BPlusTreeNode *node, int index) {
  BPlusTreeNode *childNode = node->children[index];
  BPlusTreeNode *prevChild = node->children[index - 1];

  for (int i = childNode->keysSize - 1; i >= 0; i--) {
    childNode->keys[i + 1] = childNode->keys[i];
  }

  childNode->keys[0] = prevChild->keys[prevChild->keysSize - 1];
  node->keys[index - 1] = prevChild->keys[prevChild->keysSize - 1];

  childNode->keysSize++;
  prevChild->keysSize--;
}

void borrow_next_child(BPlusTreeNode *node, int index) {
  BPlusTreeNode *childNode = node->children[index];
  BPlusTreeNode *nextChild = node->children[index + 1];

  childNode->keys[childNode->keysSize] = node->keys[index];

  node->keys[index] = nextChild->keys[0];

  for (int i = 1; i < nextChild->keysSize; i++) {
    nextChild->keys[i - 1] = nextChild->keys[i];
  }

  if (!nextChild->isLeaf) {
    for (int i = 1; i <= nextChild->keysSize; i++) {
      nextChild->children[i - 1] = nextChild->children[i];
    }
  }

  childNode->keysSize++;
  nextChild->keysSize--;
}

void merge_bplustree_nodes(BPlusTreeNode *node, int index) {
  BPlusTreeNode *childNode = node->children[index];
  BPlusTreeNode *nextChild = node->children[index + 1];

  childNode->keys[T - 1] = node->keys[index];

  for (int i = 0; i < nextChild->keysSize; i++) {
    childNode->keys[i + T - 1] = nextChild->keys[i];
  }

  if (!childNode->isLeaf) {
    for (int i = 0; i <= nextChild->keysSize; i++) {
      childNode->children[i + T] = nextChild->children[i];
    }
  }

  for (int i = index + 1; i < node->keysSize; i++) {
    node->keys[i - 1] = node->keys[i];
    node->children[i] = node->children[i + 1];
  }

  childNode->keysSize += nextChild->keysSize;
  node->keysSize--;

  free(nextChild);
}

int fill_child(BPlusTreeNode *node, int index) {
  BPlusTreeNode *childNode = node->children[index];

  if (index != 0 && node->children[index - 1]->keysSize >= T) {
    borrow_prev_child(node, index);
    return index;
  } else if (index != node->keysSize &&
             node->children[index + 1]->keysSize >= T) {
    borrow_next_child(node, index);
    return index;
  } else if (index != 0) {
    merge_bplustree_nodes(node, index - 1);
    return index - 1;
  } else {
    merge_bplustree_nodes(node, index);
    return index;
  }
}

void delete_from_node(BPlusTreeNode *root, int key) {
  int index = 0;
  while (index < root->keysSize && key > root->keys[index]) {
    index++;
  }
  if (index < root->keysSize && key == root->keys[index]) {
    if (root->isLeaf) {
      delete_from_leaf(root, index);
    } else {
      delete_from_non_leaf(root, index);
    }
  } else {
    if (root->isLeaf) {
      return; // key not found
    }
    bool lastKey = index == root->keysSize;
    BPlusTreeNode *childNode = root->children[index];
    if (childNode->keysSize < T) {
      fill_child(root, index);
    }
    if (lastKey && index > root->keysSize) {
      delete_from_node(root->children[index - 1], key);
    } else {
      delete_from_node(root->children[index], key);
    }
  }
}

int get_predecessor(BPlusTreeNode *node, int index) {
  BPlusTreeNode *currNode = node->children[index];
  while (!currNode->isLeaf) {
    currNode = currNode->children[currNode->keysSize];
  }
  return currNode->keys[currNode->keysSize - 1];
}

int get_successor(BPlusTreeNode *node, int index) {
  BPlusTreeNode *currNode = node->children[index + 1];
  while (!currNode->isLeaf) {
    currNode = currNode->children[0];
  }
  return currNode->keys[0];
}

void delete_from_non_leaf(BPlusTreeNode *root, int index) {
  int key = root->keys[index];
  BPlusTreeNode *prevChild = root->children[index];
  BPlusTreeNode *nextChild = root->children[index + 1];

  if (prevChild->keysSize >= T) {
    if (prevChild->isLeaf) {
      root->keys[index] = prevChild->keys[prevChild->keysSize - 1];
      nextChild->keys[0] = prevChild->keys[prevChild->keysSize - 1];
      prevChild->keysSize--;
    } else {
      int predecessor = get_predecessor(root, index);
      root->keys[index] = predecessor;
      delete_from_node(prevChild, predecessor);
    }
  } else if (nextChild->keysSize >= T) {
    if (nextChild->isLeaf) {
      delete_from_leaf(nextChild, 0);
      root->keys[index] = nextChild->keys[0];
    } else {
      int successor = get_successor(root, index);
      root->keys[index] = successor;
      delete_from_node(nextChild, successor);
    }
  } else {
    merge_bplustree_nodes(root, index);
    delete_from_node(prevChild, key);
  }
}

void delete_bplustree_node(BPlusTreeNode *root, int key) {
  int i = 0;

  while (i < root->keysSize && key >= root->keys[i]) {
    i++;
  }

  if (root->isLeaf) {
    if (i > 0 && key == root->keys[i - 1]) {
      delete_from_leaf(root, i - 1);
    } else {
      return; // key not found
    }
    return;
  } else if (i > 0 && key == root->keys[i - 1]) {
    delete_from_non_leaf(root, i - 1);
    return;
  }

  if (!root->isLeaf && root->children[i]->keysSize < T) {
    i = fill_child(root, i);
  }

  delete_bplustree_node(root->children[i], key);
  return;
}
