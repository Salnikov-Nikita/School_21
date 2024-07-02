#include <stdio.h>

#include "bst.h"

void bst_traverse_test_1(void);
void bst_traverse_test_2(void);
int test_1_cmp(int item1, int item2);
int test_2_cmp(int item1, int item2);
void print_func(int item);

int main(void) {
  printf("bst_traverse_test_1:\n");
  bst_traverse_test_1();
  printf("bst_traverse_test_2:\n");
  bst_traverse_test_2();
}

void print_func(int item) { printf(" %d", item); }

int test_1_cmp(int item1, int item2) { return item1 - item2; }

void bst_traverse_test_1(void) {
  t_btree *root = bstree_create_node(10);
  bstree_insert(root, 5, test_1_cmp);
  bstree_insert(root, 1, test_1_cmp);
  bstree_insert(root, 25, test_1_cmp);
  bstree_insert(root, 20, test_1_cmp);
  bstree_insert(root, 3, test_1_cmp);
  bstree_insert(root, 15, test_1_cmp);
  printf("infix:");
  bstree_apply_infix(root, print_func);
  printf("\n");
  printf("prefix:");
  bstree_apply_prefix(root, print_func);
  printf("\n");
  printf("postfix:");
  bstree_apply_postfix(root, print_func);
  printf("\n");
  bstree_destroy(root);
}

int test_2_cmp(int item1, int item2) { return item2 - item1; }

void bst_traverse_test_2(void) {
  t_btree *root = bstree_create_node(50);
  bstree_insert(root, 20, test_2_cmp);
  bstree_insert(root, 11, test_2_cmp);
  bstree_insert(root, 76, test_2_cmp);
  bstree_insert(root, 102, test_2_cmp);
  bstree_insert(root, 80, test_2_cmp);
  bstree_insert(root, 42, test_2_cmp);
  printf("infix:");
  bstree_apply_infix(root, print_func);
  printf("\n");
  printf("prefix:");
  bstree_apply_prefix(root, print_func);
  printf("\n");
  printf("postfix:");
  bstree_apply_postfix(root, print_func);
  printf("\n");
  bstree_destroy(root);
}
