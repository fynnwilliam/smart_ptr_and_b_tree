#include <iostream>
#include <queue>

#include "b_tree.h"

void print(node *n) {
  if (!n) return;

  print(n->left);
  print(n->right);

  std::cout << n->key << ' ';
}

void print_rows(node *n) {
  std::queue<node*> q;
  q.push(n);

  while (!q.empty()) {
    n = q.front();
    std::cout << n->key << ' ';

    if (n->left) q.push(n->left);
    if (n->right) q.push(n->right);

    q.pop();
  }
}

int main() {
  b_tree tree{20};

  tree.build(tree.root(), 3);
  print(tree.root());

  std::cout << '\n';

  print_rows(tree.root());

  std::cout << '\n';
}
