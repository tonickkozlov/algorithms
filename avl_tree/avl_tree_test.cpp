#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../catch.hpp"
#include "avl_tree.h"

using namespace avl_tree;
using namespace std;
TEST_CASE( "Tree can be created", "[tree]" ) {
    node* root = new node('B',
        new node('A'),
        new node('C')
    );
    REQUIRE( root->value == 'B' );
    REQUIRE( root->left->value == 'A' );
    REQUIRE( root->right->value == 'C' );
}

TEST_CASE( "Tree nodes have parents on creation") {
    node* root = new node('B',
        new node('A'),
        new node('C')
    );
    REQUIRE( root->value == 'B' );
    REQUIRE( root->left->parent == root );
    REQUIRE( root->right->parent == root );
}

TEST_CASE( "Tree height can be found" ) {
    node simple = node('0');
    REQUIRE(height(&simple) == 1);
    node root = node('A', new node('B', new node('C')));
    REQUIRE(height(&root) == 3);
}

TEST_CASE( "Tree width can be found" ) {
    node simple = node('0');
    REQUIRE(width(&simple) == 1);
    node root = node('A',
                    new node('B', new node('C')),
                    new node('D'));
    REQUIRE(width(&root) == 4);
}

TEST_CASE( "Count of nodes under tree can be found" ) {
    node simple = node('0');
    REQUIRE(count(&simple) == 1);
    node root = node('A',
                    new node('B',
                        new node('C'),
                        new node('M')),
                    new node('D',
                        new node('E')));
    REQUIRE(count(&root) == 6);
}

TEST_CASE( "Finding next node from existing" ) {
    REQUIRE(next(nullptr) == nullptr);
    node *root = new node('A',
                    nullptr,
                    new node('C',
                        new node('B')));
    REQUIRE(next(root)->value == 'B');
    root = new node('A');
    REQUIRE(next(root) == nullptr);
    root = new node('D',
                new node('A',
                    nullptr,
                    new node('B',
                        nullptr,
                        new node('D'))));
    REQUIRE(next(root->left->right->right) == root);
    root = new node('C',
                new node('B',
                    new node('A')));
    REQUIRE(next(root->left->left) == root->left);
}

TEST_CASE( "Inorder traversal" ) {
    node root = node('A',
                    new node('B',
                        new node('C'),
                        new node('M')),
                    new node('D',
                        new node('E')));
    REQUIRE(inorder(&root) == "CBMAED");
}

TEST_CASE( "Inorder traversal using next()" ) {
    node *root = new node('A',
                    new node('B',
                        new node('C'),
                        new node('M')),
                    new node('D',
                        new node('E')));
    REQUIRE(inorderNext(root) == "CBMAED");
}

TEST_CASE( "Building a tree from traversal" ) {
    node *root = make_tree("ABCDEFG");
    REQUIRE(root->value == 'D');
    REQUIRE(inorder(root) == "ABCDEFG");
    REQUIRE(root->left->parent == root);

    delete(root);
    root = make_tree("AB");
    REQUIRE(root->value == 'B');
    REQUIRE(inorder(root) == "AB");
}

TEST_CASE( "Small left rotation ") {
    node *root = new node('B',
                    new node('A'),
                    new node('D',
                        new node('C'),
                        new node('F',
                            new node('E'),
                            new node('G'))));
    REQUIRE(inorder(root) == "ABCDEFG");
    REQUIRE(inorderNext(root) == "ABCDEFG");
    REQUIRE(balanceFactor(root) == 2);
    print(root);
    root = rotateLeft(root, root->right);
    print(root);
    REQUIRE(balanceFactor(root) == 0);
    REQUIRE(inorder(root) == "ABCDEFG");
    // // makes sure parent pointers are correct
    REQUIRE(inorderNext(root) == "ABCDEFG");
}

TEST_CASE( "Small rigth rotation ") {
    node *root = new node('F',
                    new node('D',
                        new node('B',
                            new node('A'),
                            new node('C')),
                        new node('E')),
                    new node('G'));
    REQUIRE(inorder(root) == "ABCDEFG");
    REQUIRE(inorderNext(root) == "ABCDEFG");
    REQUIRE(balanceFactor(root) == -2);
    print(root);
    root = rotateRight(root, root->left);
    print(root);
    REQUIRE(balanceFactor(root) == 0);
    REQUIRE(inorder(root) == "ABCDEFG");
    // makes sure parent pointers are correct
    REQUIRE(inorderNext(root) == "ABCDEFG");
}

TEST_CASE( "Finding node's parent" ) {
    node *root = new node('M',
                    new node('D'),
                    new node('O',
                        nullptr,
                        new node('S',
                            nullptr,
                            new node('T'))));

    REQUIRE(parent(root, root) == nullptr);
    REQUIRE(parent(root, root->right->right) == root->right);
    REQUIRE(parent(root, root->left) == root);
}

TEST_CASE( "Inserting a new node" ) {
    node *root = make_tree("ABCDEFG");
    // insert(root, 'H');
    // REQUIRE(inorder(root) == "ABCDEFGH");
    // delete(root);
    //
    // root = make_tree("ABCDEFG");
    // insert(root, 'D');
    // REQUIRE(inorder(root) == "ABCDDEFG");
    // delete(root);

    root = new node('D', new node('B'));
    root = insert(root, 'C');
    cout << "INSERTED" << endl;
    REQUIRE(inorder(root) == "BCD");
    REQUIRE(balanceFactor(root) == 0);

    root = new node('M',
                    new node('D'),
                    new node('O',
                        nullptr,
                        new node('S')));

    // requires a left rotation
    root = insert(root, 'T');
    REQUIRE(inorder(root) == "DMOST");
    REQUIRE(inorderNext(root) == "DMOST");
    // tree is balanced
    REQUIRE(balanceFactor(root) == 1);
    print(root);

    root =  new node('S',
                new node('O',
                    new node('M'),
                    nullptr),
                new node('T'));
    print(root);
    root = insert(root, 'D');
    REQUIRE(balanceFactor(root) == -1);
}

TEST_CASE( "Balancing an alphabeth" ) {
    cout << "--------------------" << endl;
    node *root = new node('M');
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c != 'M') {
            root = insert(root, c);
        }
    }
    REQUIRE(height(root) == ceil(log2(26)));
    REQUIRE(abs(balanceFactor(root)) < 2);
}
