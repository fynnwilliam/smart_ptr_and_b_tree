#include <iostream>
#include "b_tree.h"

int main()
{
    b_tree b;
    
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
}
