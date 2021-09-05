class node
{
public:    
    int key{};
    node* left{nullptr};
    node* right{nullptr};
    node* parent{nullptr};
    
    node() = default;
    explicit node(int d) : key{d} {}
    node(node const& n) : key{n.key}, left{n.left}, right{n.right}, parent{n.parent} {}
    node(node&& n) noexcept : key{n.key}, left{n.left}, right{n.right}, parent{n.parent}
    {
        n.key = 0;
        n.left = n.right = n.parent = nullptr;
    }
    
    node& operator =(node n)
    {
        _swap(*this, n);
        
        return *this;
    }
    
    bool operator>(node const& n) const { return key > n.key; }
    
    friend void _swap(node& a, node& b)
    {
        std::swap(a.key, b.key);
        std::swap(a.left, b.left);
        std::swap(a.right, b.right);
        std::swap(a.parent, b.parent);
    }
        
    ~node() {}
};
    
class b_tree
{
public:
    node* root;
    
    b_tree() : root{nullptr} {}
    
    void _cleanup(node* n)
    {
        if (!n) return;

        _cleanup(n->left);
        _cleanup(n->right);

        n->left = n->right = n->parent = nullptr;
        
        delete n;
    }
    
    void cleanup()
    {
        _cleanup(root);
        
        root = nullptr;
    }
    
    ~b_tree()
    {
        cleanup();
    }
};

node* leftmost_key(node* n)
{
    return n->left ? leftmost_key(n->left) : n;
}

node* root_node(node* n)
{
    return n->parent ? root_node(n->parent) : n;
}

bool is_left_alligned(node* n)
{
    return n == n->parent->left;
}

[[deprecated ("please update the name of this function")]]
node* x(node* n)
{
    node* root{root_node(n)};
    return *root > *n ? root : nullptr;
}

node* in_order_successor(node* n)
{
    if (!n) return nullptr;
    
    node* u = !n->right ? n : leftmost_key(n->right);
    
    if (u == n)
    {
        return is_left_alligned(n) ? n->parent : x(n);
    }
    else return u;
}