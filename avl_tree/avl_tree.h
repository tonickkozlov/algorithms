#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <tuple>
namespace avl_tree {

    struct node {
        node(char v, node* l=nullptr, node* r=nullptr): parent(nullptr), left(l), right(r), value(v) {
            if (left) {
                left->parent = this;
            }
            if(right) {
                right->parent = this;
            }
        }
        node *parent;
        node *left;
        node *right;
        char value;
    };


    int height(const node *x) {
        if (!x) {
            return 0;
        }
        return 1 + std::max(height(x->left), height(x->right));
    }

    // counts number of nodes under root
    int count(const node *root) {
        if (!root) {
            return 0;
        }
        return 1 + count(root->left) + count(root->right);
    }

    int width(const node *x) {
        if (!x) {
            return 0;
        }
        int width = 1;
        // calculate width to the left
        for (const node* current = x->left; current; current = current->left) {
            ++width;
        }
        // calculate width to the right
        for (const node* current = x->right; current; current = current->right) {
            ++width;
        }
        return width;
    }

    int balanceFactor(const node *root) {
        if (!root) {
            return 0;
        }
        return height(root->right) - height(root->left);
    }

    std::ostream& operator << (std::ostream& os, const node &x) {
        os << x.value << "|" << balanceFactor(&x);
        return os;
    }

    // pretty-prints a tree
    void print(const node *root) {
        std::cout << std::string(20, '#') << std::endl;
        int currentLevel = 0,
            currentOffset = 0;
        // every queue node holds pointer to node, its level, and its offset from the left
        std::queue<std::tuple<const node*, int, int>> q;
        q.push(std::make_tuple(root, currentLevel, count(root->left)));
        while (!q.empty()) { // (D, 4, 1), (C, 2, 0)
            auto current = q.front(); q.pop();
            const node* currentNode = std::get<0>(current); // D
            int level = std::get<1>(current); // 1
            int offset = std::get<2>(current); // 4
            if (level != currentLevel) {
                std::cout << "\n";
                currentLevel = level;
                currentOffset = 0;
            }
            for (int i = currentOffset; i < offset; ++i) {
                std::cout << "     ";
            }
            currentOffset = offset;
            std::cout << *currentNode;
            std::cout.flush();
            if (currentNode->left) {
                q.push(std::make_tuple(currentNode->left, currentLevel+1, currentOffset - 1 - count(currentNode->left->right)));
            }
            if (currentNode->right) {
                q.push(std::make_tuple(currentNode->right, currentLevel+1, currentOffset + 1 + count(currentNode->right->left)));
            }
        }
        std::cout << std::endl;
    }

    node* make_tree(const std::string &inOrder) {
        struct stackFrame {
            node **target; // node to attach value to
            node *parent;
            std::size_t begin; // beginning of range this node covers (e.g. for root - whole string)
            std::size_t end; // end of range this node covers (e.g. for root - length of string)
        };
        std::stack<stackFrame> st;
        node *root;
        st.push(stackFrame{&root, nullptr, 0, inOrder.size()});

        while (!st.empty()) {
            stackFrame currentFrame = st.top(); st.pop();
            std::size_t middle = (currentFrame.begin + currentFrame.end) / 2;
            node *newNode = new node(inOrder[middle]);
            *(currentFrame.target) = newNode;
            newNode->parent = currentFrame.parent;
            if (middle > currentFrame.begin) {
                st.push(stackFrame{&newNode->left, newNode, currentFrame.begin, middle});
            }
            if (middle+1 < currentFrame.end) {
                st.push(stackFrame{&newNode->right, newNode, middle+1, currentFrame.end});
            }
        }
        return root;
    }

    node* parent(node *root, node *child) {
        if (!child || root == child) {
            return nullptr;
        }
        node *current = root;
        while (current && current->left != child && current->right != child) {
            current = child->value > current->value ? current->right : current->left;
        }
        return current;
    }

    // finds next node of the tree in in-order traversal
    node *next(node *x) {
        if (!x) {
            return nullptr;
        }
        if (x->right) {
            x = x->right;
            // find leftmost child of x->right
            while (x->left) {
                x = x->left;
            }
            return x;
        } else {
            // find first ancestor on the left
            while (x->parent && (x->parent->right == x)) {
                x = x->parent;
            }
            return x->parent;
        }
    }

    std::string inorder(const node *root) {
        std::string result;
        std::stack<const node*> st;
        std::set<const node*> visited;

        st.push(root);
        while (!st.empty()) {
            const node* current = st.top();
            visited.insert(current);
            if (current->left && (visited.find(current->left) == visited.end())) {
                st.push(current->left);
                continue;
            }
            result += current->value; st.pop();
            if (current->right && (visited.find(current->right) == visited.end())) {
                st.push(current->right);
            }
        }
        return result;
    }

    std::string inorderNext(node *x) {
        // find leftmost
        while (x->left) {
            x = x->left;
        }
        std::string result;
        for(; x; x = next(x)) {
            std::cout.flush();
            result += x->value;
        }
        return result;
    }

    node *rotateLeft(node *root, node *x) {
        root->right = x->left;
        if (root->right) {
            root->right->parent = root;
        }
        // fix parent pointer
        x->parent = root->parent;
        if (x->parent) {
            if (root->parent->left == root) {
                root->parent->left = x;
            } else {
                root->parent->right = x;
            }
        }
        root->parent = x;
        x->left = root;
        return x;
    }

    node *rotateRight(node *root, node *x) {
        root->left = x->right;
        if (root->left) {
            root->left->parent = root;
        }

        x->parent = root->parent;
        if (x->parent) {
            if (root->parent->left == root) {
                root->parent->left = x;
            } else {
                root->parent->right = x;
            }
        }

        root->parent = x;
        x->right = root;
        return x;
    }

    // balance a tree when a new node has been incerted under x
    node* balance(node *x) {
        // parent of the parent of currently inserted node
        for(; x->parent; x = x->parent ? x->parent : x) {
            if (balanceFactor(x->parent) == +2) {
                if (balanceFactor(x) < 0) {
                    x = rotateRight(x, x->left);
                }
                x = rotateLeft(x->parent, x);
            } else if (balanceFactor(x->parent) == -2) {
                if (balanceFactor(x) > 0) {
                    x = rotateLeft(x, x->right);
                }
                x = rotateRight(x->parent, x);
            }
        }
        return x;
    }

    node* insert(node *root, char c) {
        if (!root)
            return nullptr;
        node *parent = root;
        while (true) {
            if (c >= parent->value && parent->right) {
                parent = parent->right;
            } else if (c < parent->value && parent->left) {
                parent = parent->left;
            } else {
                break;
            }
        }
        node **target = (c > parent->value) ? &parent->right : &parent->left;
        *target = new node(c);
        (*target)->parent = parent;
        return balance(parent);
    }
}
