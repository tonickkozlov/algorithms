#ifndef __TREES_H_
#define __TREES_H_
#include <iostream>
struct node {
    char value;
    node *left;
    node *right;
};

node *make_node(char value, node* left=nullptr, node *right=nullptr) {
    node *current = new node{value, left, right};
    return current;
}

void inOrder(const node *root) {
    if (!root) return;
    inOrder(root->left);
    std::cout << root->value << " ";
    inOrder(root->right);
}
#endif
