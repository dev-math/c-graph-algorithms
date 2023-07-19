#include "../include/btree.h"
#include <stdio.h>
#include <stdlib.h>

BTreeNode *create_btree_node() {
  BTreeNode *ptr = (BTreeNode *)malloc(sizeof(BTreeNode));
  if (ptr == NULL) {
    fprintf(stderr, "Error: Could not allocate memory!\n");
    return NULL;
  }

  ptr->isLeaf = true;
  ptr->keys = (int *)malloc(sizeof(int) * MAX_KEYS);
  ptr->children = (BTreeNode **)malloc(sizeof(BTreeNode *) * MAX_CHILDREN);
  if (!ptr->keys || !ptr->children) {
    free(ptr->keys);
    free(ptr->children);
    free(ptr);
    return NULL;
  }

  for (int i = 0; i < MAX_CHILDREN; i++) {
    ptr->children[i] = NULL;
  }

  return ptr;
}

BTreeNode *create_btree() { return create_btree_node(); }

BTreeNode *search_btree_node(BTreeNode *node, int key) {
  if (!node) {
    return NULL;
  }

  int i = 0;
  while (i < node->keysSize && key > node->keys[i]) {
    i++;
  }

  if (i < node->keysSize && key == node->keys[i]) {
    return node;
  } else if (node->isLeaf) {
    return NULL;
  } else {
    return search_btree_node(node->children[i], key);
  }

  return NULL;
}

void delete_internal_node(BTreeNode **root, BTreeNode *x, int k, int i);
int delete_predecessor(BTreeNode **root, BTreeNode *x);
int delete_successor(BTreeNode **root, BTreeNode *x);
void delete_merge(BTreeNode **root, BTreeNode *x, int i, int j);
void delete_sibling(BTreeNode **root, BTreeNode *x, int i, int j);

void delete_btree_node(BTreeNode **root, BTreeNode *x, int k) {
  int t = T;
  int i = 0;

  while (i < x->keysSize && k > x->keys[i]) {
    i++;
  }
  if (x->isLeaf) {
    if (i < x->keysSize && x->keys[i] == k) {
      // Remove the key if found
      for (int j = i; j < x->keysSize - 1; j++) {
        x->keys[j] = x->keys[j + 1];
      }
      x->keysSize--;
    }
    return;
  }

  if (i < x->keysSize && x->keys[i] == k) {
    // Delete the key from the internal node
    delete_internal_node(root, x, k, i);
  } else if (x->children[i]->keysSize >= t) {
    // Recurse to the appropriate child node
    delete_btree_node(root, x->children[i], k);
  } else {
    // If the child node has fewer than t keys, handle merging or borrowing
    if (i != 0 && i + 2 < x->keysSize) {
      if (x->children[i - 1]->keysSize >= t) {
        delete_sibling(root, x, i, i - 1);
      } else if (x->children[i + 1]->keysSize >= t) {
        delete_sibling(root, x, i, i + 1);
      } else {
        delete_merge(root, x, i, i + 1);
      }
    } else if (i == 0) {
      if (x->children[i + 1]->keysSize >= t) {
        delete_sibling(root, x, i, i + 1);
      } else {
        delete_merge(root, x, i, i + 1);
      }
    } else if (i + 1 == x->keysSize) {
      if (x->children[i - 1]->keysSize >= t) {
        delete_sibling(root, x, i, i - 1);
      } else {
        delete_merge(root, x, i, i - 1);
      }
    }
    delete_btree_node(root, x->children[i], k);
  }
}

void delete_internal_node(BTreeNode **root, BTreeNode *x, int k, int i) {
  int t = T;
  if (x->isLeaf) {
    if (x->keys[i] == k) {
      // Remove the key if found
      for (int j = i; j < x->keysSize - 1; j++) {
        x->keys[j] = x->keys[j + 1];
      }
      x->keysSize--;
    }
    return;
  }

  if (x->children[i]->keysSize >= t) {
    // Replace the key with the predecessor and remove the predecessor from its
    // original position
    x->keys[i] = delete_predecessor(root, x->children[i]);
  } else if (x->children[i + 1]->keysSize >= t) {
    // Replace the key with the successor and remove the successor from its
    // original position
    x->keys[i] = delete_successor(root, x->children[i + 1]);
  } else {
    // Merge the child nodes and then delete recursively from the merged node
    delete_merge(root, x, i, i + 1);
    delete_internal_node(root, x->children[i], k, t - 1);
  }
}

int delete_predecessor(BTreeNode **root, BTreeNode *x) {
  int t = T;
  if (x->isLeaf) {
    // Remove and return the last key from the leaf node
    x->keysSize--;
    return x->keys[x->keysSize];
  }
  int n = x->keysSize - 1;
  if (x->children[n]->keysSize >= t) {
    // If the leftmost child has at least t keys, borrow the predecessor from it
    return delete_predecessor(root, x->children[n]);
  } else {
    // Merge the leftmost child with its right sibling
    delete_merge(root, x, n, n + 1);
    return delete_predecessor(root, x->children[n]);
  }
}

int delete_successor(BTreeNode **root, BTreeNode *x) {
  int t = T;
  if (x->isLeaf) {
    // Remove and return the first key from the leaf node
    int key = x->keys[0];
    for (int i = 1; i < x->keysSize; i++) {
      x->keys[i - 1] = x->keys[i];
    }
    x->keysSize--;
    return key;
  }
  if (x->children[1]->keysSize >= t) {
    // If the rightmost child has at least t keys, borrow the successor from it
    return delete_successor(root, x->children[1]);
  } else {
    // Merge the rightmost child with its left sibling
    delete_merge(root, x, 0, 1);
    return delete_successor(root, x->children[0]);
  }
}

void delete_merge(BTreeNode **root, BTreeNode *x, int i, int j) {
  BTreeNode *cnode = x->children[i];
  BTreeNode *new = NULL;

  if (j > i) {
    BTreeNode *rsnode = x->children[j];
    // Merge keys and children from the right sibling into the current node
    cnode->keys[cnode->keysSize] = x->keys[i];
    for (int k = 0; k < rsnode->keysSize; k++) {
      cnode->keys[cnode->keysSize + k + 1] = rsnode->keys[k];
      if (rsnode->children) {
        cnode->children[cnode->keysSize + k + 1] = rsnode->children[k];
      }
    }
    if (rsnode->children) {
      cnode->children[cnode->keysSize + rsnode->keysSize + 1] =
          rsnode->children[rsnode->keysSize];
    }
    cnode->keysSize += rsnode->keysSize + 1;
    x->keysSize--;
    for (int k = i; k < x->keysSize; k++) {
      x->keys[k] = x->keys[k + 1];
      x->children[k + 1] = x->children[k + 2];
    }
    new = cnode;
    free(rsnode);
  } else {
    BTreeNode *lsnode = x->children[j];
    // Merge keys and children from the left sibling into the current node
    for (int k = cnode->keysSize - 1; k >= 0; k--) {
      cnode->keys[k + 1] = cnode->keys[k];
      cnode->children[k + 2] = cnode->children[k + 1];
    }
    cnode->keys[0] = x->keys[j];
    for (int k = lsnode->keysSize - 1; k >= 0; k--) {
      cnode->keys[k] = lsnode->keys[k];
      if (lsnode->children) {
        cnode->children[k + 1] = lsnode->children[k];
      }
    }
    if (lsnode->children) {
      cnode->children[0] = lsnode->children[lsnode->keysSize];
    }
    cnode->keysSize += lsnode->keysSize + 1;
    x->keysSize--;
    for (int k = j; k < x->keysSize; k++) {
      x->keys[k] = x->keys[k + 1];
      x->children[k] = x->children[k + 1];
    }
    new = cnode;
    free(lsnode);
  }

  if (x->keysSize == 0 && x != *root) {
    // The current node is not the root and has no keys after the merge, so free
    // it
    free(x->keys);
    free(x->children);
    free(x);
  }

  if (x == *root && x->keysSize == 0) {
    // The root has no keys after the merge, so set the new root
    *root = new;
  }
}

void delete_sibling(BTreeNode **root, BTreeNode *x, int i, int j) {
  BTreeNode *cnode = x->children[i];
  if (i < j) {
    BTreeNode *rsnode = x->children[j];
    // Borrow the key from the right sibling
    cnode->keys[cnode->keysSize] = x->keys[i];
    x->keys[i] = rsnode->keys[0];
    if (rsnode->children) {
      cnode->children[cnode->keysSize + 1] = rsnode->children[0];
      for (int k = 0; k < rsnode->keysSize; k++) {
        rsnode->keys[k] = rsnode->keys[k + 1];
        rsnode->children[k] = rsnode->children[k + 1];
      }
      rsnode->children[rsnode->keysSize] =
          rsnode->children[rsnode->keysSize + 1];
    } else {
      for (int k = 0; k < rsnode->keysSize; k++) {
        rsnode->keys[k] = rsnode->keys[k + 1];
      }
    }
    cnode->keysSize++;
    rsnode->keysSize--;
  } else {
    BTreeNode *lsnode = x->children[j];
    // Borrow the key from the left sibling
    for (int k = cnode->keysSize; k > 0; k--) {
      cnode->keys[k] = cnode->keys[k - 1];
      cnode->children[k + 1] = cnode->children[k];
    }
    cnode->keys[0] = x->keys[i - 1];
    if (lsnode->children) {
      cnode->children[1] = lsnode->children[lsnode->keysSize];
    }
    x->keys[i - 1] = lsnode->keys[lsnode->keysSize - 1];
    cnode->keysSize++;
    lsnode->keysSize--;
  }
}

void split_child(BTreeNode *parent, int index) {
  BTreeNode *child = parent->children[index]; // full child

  BTreeNode *new_child = create_btree_node();
  new_child->isLeaf = child->isLeaf;
  // new_child->keysSize = T - 1; // TODO: see if I need this
  parent->children[index + 1] = new_child;

  // insert the median of the full child into parent
  int median = T - 1;
  parent->keys[index] = child->keys[median];
  parent->keysSize++;

  // split the full child keys with the new child
  // the new_child will take keys from median + 1 onwards
  new_child->keysSize = median;
  child->keysSize = median;
  for (int i = 0; i < median; i++) {
    new_child->keys[i] = child->keys[i + T];
  }

  if (!child->isLeaf) {
    // new_child will take children from index T onwards
    for (int i = 0; i < median + 1; i++) {
      new_child->children[i] = child->children[i + T];
    }
  }
}

bool insert_into_non_full(BTreeNode *node, int key) {
  int i = node->keysSize - 1;
  if (node->isLeaf) {
    while (i >= 0 && key < node->keys[i]) {
      node->keys[i + 1] = node->keys[i];
      i--;
    }
    node->keys[i + 1] = key;
    node->keysSize++;
    return true;
  } else {
    while (i >= 0 && key < node->keys[i]) {
      i--;
    }
    i++;

    bool isChildNodeFull = node->children[i]->keysSize == MAX_KEYS;
    if (isChildNodeFull) {
      split_child(node, i);
      if (key > node->keys[i]) {
        i++;
      }
    }
    return insert_into_non_full(node->children[i], key);
  }
}

bool insert_btree_node(BTreeNode **root, int key) {
  if (!*root) {
    *root = create_btree_node();
    if (!*root) {
      return false;
    }

    (*root)->keys[0] = key;
    (*root)->keysSize = 1;
    return true;
  }

  bool isRootFull = (*root)->keysSize == MAX_KEYS;
  if (isRootFull) {
    BTreeNode *newRoot = create_btree_node();
    if (!newRoot) {
      return false;
    }

    newRoot->isLeaf = false;
    newRoot->children[0] = *root;
    *root = newRoot;
    split_child(newRoot, 0);
    return insert_into_non_full(newRoot, key);
  } else {
    return insert_into_non_full(*root, key);
  }
}

void print_btree(BTreeNode *node, int level) {
  if (node) {
    printf("Level %d: ", level);
    for (int i = 0; i < node->keysSize; i++) {
      printf("%d ", node->keys[i]);
    }
    printf("\n");

    if (!node->isLeaf) {
      for (int i = 0; i <= node->keysSize; i++) {
        print_btree(node->children[i], level + 1);
      }
    }
  }
}

void free_btree(BTreeNode *node) {
  if (node) {
    if (!node->isLeaf) {
      for (int i = 0; i <= node->keysSize; i++) {
        free_btree(node->children[i]);
      }
    }
    free(node->keys);
    free(node->children);
    free(node);
  }
}
