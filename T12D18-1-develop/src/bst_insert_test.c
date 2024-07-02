#include <stdio.h>

#include "bst.h"

int bst_insert_test_1(void);
int bst_insert_test_2(void);
int test_1_cmp(int item1, int item2);
int test_2_cmp(int item1, int item2);

int main(void) {
  printf("bst_insert_test_1 - %s\n", bst_insert_test_1() ? "SUCCESS" : "FAIL");
  printf("bst_insert_test_2 - %s\n", bst_insert_test_2() ? "SUCCESS" : "FAIL");
}

#define TEST_INSERT(item_value, cmp, location)                                 \
  bstree_insert(root, (item_value), cmp);                                      \
  ok = ok && root->location->item == (item_value);                             \
  printf("inserted %d: root->%s->item is %d\n", (item_value), #location,       \
         root->location->item);

int test_1_cmp(int item1, int item2) { return item1 - item2; }

int bst_insert_test_1(void) {
  int ok = 1;
  t_btree *root = bstree_create_node(10);
  TEST_INSERT(5, test_1_cmp, left)
  TEST_INSERT(1, test_1_cmp, left->left)
  TEST_INSERT(25, test_1_cmp, right)
  TEST_INSERT(20, test_1_cmp, right->left)
  TEST_INSERT(3, test_1_cmp, left->left->right)
  TEST_INSERT(15, test_1_cmp, right->left->left)
  bstree_destroy(root);
  return ok;
}

int test_2_cmp(int item1, int item2) { return item2 - item1; }

int bst_insert_test_2(void) {
  int ok = 1;
  t_btree *root = bstree_create_node(50);
  TEST_INSERT(20, test_2_cmp, right)
  TEST_INSERT(11, test_2_cmp, right->right)
  TEST_INSERT(76, test_2_cmp, left)
  TEST_INSERT(102, test_2_cmp, left->left)
  TEST_INSERT(80, test_2_cmp, left->left->right)
  TEST_INSERT(42, test_2_cmp, right->left)
  bstree_destroy(root);
  return ok;
}
