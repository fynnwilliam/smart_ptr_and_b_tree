#include <iostream>

class node {
public:
  int key{};
  int height{};
  node *left{nullptr};
  node *right{nullptr};
  node *parent{nullptr};

  node() = default;
  explicit node(int d) : key{d} {}
  node(node const &n) : key{n.key} {}
  node(node &&n) noexcept = default;
  node &operator=(node n) { return *this = std::move(n); }

  bool operator>(node const &n) const { return key > n.key; }
  bool operator==(node const &n) const = default;
  ~node() = default;
};

class b_tree {
private:
  node *root_{nullptr};

  void _cleanup(node *n) {
    if (!n) return;

    _cleanup(n->left);
    _cleanup(n->right);

    delete n;
  }

  void _cleanup() {
    _cleanup(root_);
    root_ = nullptr;
  }

public:

  explicit b_tree(int r) : root_{new node{r}} {}
  node* root() const { return root_; }
  ~b_tree() { _cleanup(); }
};

node *leftmost_key(node *n) { return n->left ? leftmost_key(n->left) : n; }

node *root_node(node *n) { return n->parent ? root_node(n->parent) : n; }

bool is_left_alligned(node *n) { return n == n->parent->left; }

node *climb(node *n) {
  node *root{root_node(n)};
  return *root > *n ? root : nullptr;
}

node *in_order_successor(node *n) {
  if (!n) return nullptr;

  node *u = !n->right ? n : leftmost_key(n->right);

  if (u == n) {
    return is_left_alligned(n) ? n->parent : climb(n);
  }
  return u;
}
