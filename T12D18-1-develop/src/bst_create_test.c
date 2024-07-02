#include <stdio.h>

#include "bst.h"

int bst_create_test(int item);

int main(void) {
  printf("test 1 - %s\n", bst_create_test(42) ? "SUCCESS" : "FAIL");
  printf("test 2 - %s\n", bst_create_test(-1) ? "SUCCESS" : "FAIL");
}

int bst_create_test(int item) {
  t_btree *root = bstree_create_node(item);
  printf("bst_create_test: %p, %p, %d\n", root->left, root->right, root->item);
  int ok = root->left == NULL && root->right == NULL && root->item == item;
  bstree_destroy(root);
  return ok;
}
