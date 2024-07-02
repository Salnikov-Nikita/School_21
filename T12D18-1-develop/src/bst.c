#include <stdlib.h>

#include "bst.h"

t_btree *bstree_create_node(int item) {
  t_btree *node = malloc(sizeof(t_btree));
  if (node != NULL) {
    node->left = NULL;
    node->right = NULL;
    node->item = item;
  }
  return node;
}

void bstree_destroy(t_btree *root) {
  if (root != NULL) {
    bstree_destroy(root->left);
    bstree_destroy(root->right);
    free(root);
  }
}

void bstree_insert(t_btree *root, int item, int (*cmpf)(int, int)) {
  int cmp = root != NULL;
  while (cmp != 0) {
    cmp = cmpf(item, root->item);
    if (cmp < 0) {
      if (root->left == NULL) {
        root->left = bstree_create_node(item);
        cmp = 0;
      } else {
        root = root->left;
      }
    } else if (cmp > 0) {
      if (root->right == NULL) {
        root->right = bstree_create_node(item);
        cmp = 0;
      } else {
        root = root->right;
      }
    }
  }
}

void bstree_apply_infix(t_btree *root, void (*applyf)(int)) {
  if (root != NULL) {
    bstree_apply_infix(root->left, applyf);
    applyf(root->item);
    bstree_apply_infix(root->right, applyf);
  }
}

void bstree_apply_prefix(t_btree *root, void (*applyf)(int)) {
  if (root != NULL) {
    applyf(root->item);
    bstree_apply_infix(root->left, applyf);
    bstree_apply_infix(root->right, applyf);
  }
}

void bstree_apply_postfix(t_btree *root, void (*applyf)(int)) {
  if (root != NULL) {
    bstree_apply_infix(root->left, applyf);
    bstree_apply_infix(root->right, applyf);
    applyf(root->item);
  }
}
