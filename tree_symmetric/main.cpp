/**
 * Find if a tree is symmetric against it's root
 */
#include <vector>
#include <string>
#include <map>

#include <iostream>
#include "../trees/trees.h"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

// tests if two trees are symmetric
bool treesSymmetric(node *left, node *right) {
    if (!left && !right) {
        return true;
    }
    if (!left || !right) {
        return false;
    }
    return (left->value == right->value &&
        treesSymmetric(left->right, right->left) &&
        treesSymmetric(left->left, right->right)
    );
}

bool treeSymmetric(node *root) {
    return !root || treesSymmetric(root->left, root->right);
}


TEST_CASE("Symmetry") {
    node *root = make_node('A',
            make_node('F',
                make_node('B'),
                make_node('D')
                ),
            make_node('F',
                make_node('D'),
                make_node('B')
                )
            );
    REQUIRE(treeSymmetric(root) == true);
    REQUIRE(treeSymmetric(nullptr) == true);
}

TEST_CASE("Non-Symmetry") {
    node *root = make_node('A',
            make_node('F',
                make_node('B')
                ),
            make_node('F',
                make_node('D'),
                make_node('B')
                )
            );
    REQUIRE(treeSymmetric(root) == false);
}
