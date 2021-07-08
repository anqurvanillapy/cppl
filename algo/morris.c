/**
 * Morris Traversal
 * ================
 */

#include <stdio.h>

typedef struct tree {
  struct tree *left;
  struct tree *right;
  int value;
} tree;

void inorder(tree *root, void (*f)(int t)) {
  tree *cursor = root;
  while (cursor != NULL) {
    if (cursor->left == NULL) {
      f(cursor->value);
      cursor = cursor->right;
    } else {
      tree *pre = cursor->left;
      while (pre->right != NULL && pre->right != cursor) {
        pre = pre->right;
      }
      if (pre->right == NULL) {
        pre->right = cursor;
        cursor = cursor->left;
      } else {
        f(cursor->value);
        pre->right = NULL;
        cursor = cursor->right;
      }
    }
  }
}

void visit(int t) { printf("%d ", t); }

int main() {
  tree t = (tree){
      .left =
          &(tree){
              .left = &(tree){.value = 3},
              .right = &(tree){.value = 4},
              .value = 2,
          },
      .right =
          &(tree){
              .left = &(tree){.value = 7},
              .right = &(tree){.value = 8},
              .value = 6,
          },
      .value = 1,
  };
  inorder(&t, visit);
}
