#include <iostream>

#include "b_tree.h"

void print(node *n) {
  if (!n) return;

  print(n->left);
  print(n->right);

  std::cout << n->key << ' ';
}

int main() {
  b_tree tree{20};

  tree.build(tree.root(), 3);
  print(tree.root());

  std::cout << '\n';
}
