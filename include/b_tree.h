class node
{
public:    
    int key{};
    node* left;
    node* right;
    node* parent;
    
    node() : key{}, left{nullptr}, right{nullptr}, parent{nullptr} {}
    explicit node(int d) : key{d}, left{nullptr}, right{nullptr}, parent{nullptr} {}
    node(node const& n) : key{n.key}, left{n.left}, right{n.right}, parent{nullptr} {}
    node(node&& n) : key{n.key}, left{n.left}, right{n.right}, parent{n.parent}
    {
        n.key = 0;
        n.left = nullptr;
        n.right = nullptr;
        n.parent = nullptr;
    }
    node& operator =(node n)
    {
        _swap(*this, n);
        
        return *this;
    }
    bool operator >(node const& n) { return key > n.key; }
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
    void _cleanup(node*& n)
    {
        if (!n) return;

        cleanup(n->left);
        cleanup(n->right);

        n->left = nullptr;
        n->right = nullptr;
        n->parent = nullptr;
        
        delete n;
    }
    void cleanup(node*& n)
    {
        _cleanup(n);
        
        n = nullptr;
    }
    ~b_tree()
    {
        cleanup(root);
    }
};

node* leftmost_key(node*& n)
{
    return n->left ? leftmost_key(n->left) : n;
}

node* root_node(node*& n)
{
    return n->parent ? root_node(n->parent) : n;
}

bool is_left_alligned_to_parent(node*& n)
{
    return n == n->parent->left;
}

[[deprecated ("please update the name of this function")]]
node* x(node*& n)
{
    node* root{root_node(n)};
    return *root > *n ? root : nullptr;
}

node* in_order_successor(node*& n)
{
    if (!n) return nullptr;
    
    node* u = !n->right ? n : leftmost_key(n->right);
    
    if (u == n)
    {
        return is_left_alligned_to_parent(n) ? n->parent : x(n);
    }
    else return u;
}