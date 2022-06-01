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
  std::unordered_set<int> set_;

  void _cleanup(node *n) {
    if (!n)
      return;

    _cleanup(n->left);
    _cleanup(n->right);

    delete n;
  }

  void _cleanup() {
    _cleanup(root_);
    root_ = nullptr;
  }

  node *left_node(node *n) {
    std::mt19937 g(std::random_device{}());
    std::uniform_int_distribution<int> d(n->key - 5, n->key - 1);

    while (true) {
      if (int a{d(g)}; !set_.count(a)) {
        if (!left_side(n) && a < 20) continue;

        set_.insert(a);
        return new node(a);
      }
    }
  }

  node *right_node(node *n) {
    std::mt19937 g(std::random_device{}());
    std::uniform_int_distribution<int> d(n->key + 1, n->key + 10);

    while (true) {
      if (int a{d(g)}; !set_.count(a)) {
        if (left_side(n) && a > 20) continue;

        set_.insert(a);
        return new node(a);
      }
    }
  }

  bool left_side(node *n) {
    static node *prev_node{n};

    if (!n->parent && !n->left)
      return n->left == nullptr;
    if (!n->parent && n->left)
      return n->left->key == prev_node->key;

    prev_node = n;
    return left_side(n->parent);
  }

public:
  explicit b_tree(int r) : root_{new node{r}}, set_{r} {}

  node *root() const { return root_; }

  void build(node *n, std::size_t height) {
    if (n && height) {
      n->left = left_node(n);
      n->right = right_node(n);
      --height;

      build(n->left, height);
      build(n->right, height);
    }
  }

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
  if (!n)
    return nullptr;

  node *u = !n->right ? n : leftmost_key(n->right);

  if (u == n) {
    return is_left_alligned(n) ? n->parent : climb(n);
  }
  return u;
}
