#include <iostream>
#include <random>
#include <unordered_set>

#include "b_tree.h"

bool left_side(node *n) {
  static node *prev_node{n};

  if (!n->parent && !n->left)
    return n->left == nullptr;
  if (!n->parent && n->left)
    return n->left->key == prev_node->key;

  prev_node = n;
  return left_side(n->parent);
}

node *right_node(node *n, std::unordered_set<int> &m) {
  std::mt19937 g(std::random_device{}());
  std::uniform_int_distribution<int> d(n->key + 1, n->key + 10);

  while (true) {
    if (int a{d(g)}; !m.count(a)) {
      if (left_side(n) && a > 20) continue;

      m.insert(a);
      return new node(a);
    }
  }
}

node *left_node(node *n, std::unordered_set<int> &m) {
  std::mt19937 g(std::random_device{}());
  std::uniform_int_distribution<int> d(n->key - 5, n->key - 1);

  while (true) {
    if (int a{d(g)}; !m.count(a)) {
      if (!left_side(n) && a < 20) continue;

      m.insert(a);
      return new node(a);
    }
  }
}

void build(node *n, std::size_t height) {
  if (n && height) {
    static std::unordered_set<int> m{n->key};

    n->left = left_node(n, m);
    n->right = right_node(n, m);
    --height;

    build(n->left, height);
    build(n->right, height);
  }
}

void print(node *n) {
  if (!n) return;

  print(n->left);
  print(n->right);

  std::cout << n->key << ' ';
}

int main() {
  b_tree b;
  b.root = new node(20);

  build(b.root, 3);
  print(b.root);

  std::cout << '\n';

  /*
  b.root = new node(20);

  b.root->left = new node(9);
  b.root->left->parent = b.root;

  b.root->right = new node(25);
  b.root->right->parent = b.root;

  b.root->left->left = new node(5);
  b.root->left->left->parent = b.root->left;

  b.root->left->right = new node(12);
  b.root->left->right->parent = b.root->left;

  b.root->left->right->left = new node(11);
  b.root->left->right->left->parent = b.root->left->right;

  b.root->left->right->right = new node(14);
  b.root->left->right->right->parent = b.root->left->right;

  b.root->right->left = new node(22);
  b.root->right->left->parent = b.root->right;

  node* test = in_order_successor(b.root->right->left);

  if (!test) std::cout << "nullptr\n" << '\n';
  else std::cout << test->key << std::endl;
  */
}
