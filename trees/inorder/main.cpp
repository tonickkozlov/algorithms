/** traverse a binary tree without recursion (stack only)
        E
  B         G
A   D    F      H
   C
*/


#include <iostream>
#include <stack>
#include "../trees.h"

using namespace std;

void inOrderNoStack(node *root) {
    stack<node*> s;
    for (node *current = root; current != nullptr; current = current->left) {
        s.push(current);
    }

    while (s.size()) {
        node *top = s.top(); s.pop();
        cout << top->value << endl;
        for (node *current = top->right; current != nullptr; current = current->left) {
            s.push(current);
        }
    }
}

int main() {
    node *root = make_node('E',
            make_node('B', 
                make_node('A'),
                make_node('D', make_node('C', make_node('c')))
                ),
            make_node('G',
                make_node('F'),
                make_node('H')
                )
            );
    inOrder(root);
    cout << endl;
    inOrderNoStack(root);
    return 0;
}
