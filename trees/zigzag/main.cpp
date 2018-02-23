/** Traverse a tree in a zig-zag manner:
          A
      B       C
   G   F    E   D
   would yield
   A C B G F E D
*/


#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
#include "../trees.h"

#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"

using namespace std;

void zigzag(node *root, ostream &os = cout) {

  struct queueNode {
    node* n;
    int level;
  };
  queue<queueNode> q;
  q.push(queueNode{root, 0});

  int currentHeight = 0;
  while (q.size()) {
    vector<node *> currentLevel;
    while (q.size() && (q.front()).level == currentHeight) {
      currentLevel.push_back(q.front().n);
      q.pop();
    }

    if (currentHeight+1 % 2 == 1) {
      for (int i = 0; i < currentLevel.size(); i++) {
        os << currentLevel[i]->value << " ";
        if (currentLevel[i]->left) {
          q.push(queueNode{currentLevel[i]->left, currentHeight+1});
        }
        if (currentLevel[i]->right) {
          q.push(queueNode{currentLevel[i]->right, currentHeight+1});
        }
      }
    } else {
      for (int i = currentLevel.size()-1; i >= 0; i--) {
        os << currentLevel[i]->value << " ";

        if (currentLevel[i]->right) {
          q.push(queueNode{currentLevel[i]->right, currentHeight+1});
        }
        if (currentLevel[i]->left) {
          q.push(queueNode{currentLevel[i]->left, currentHeight+1});
        }
      }
    }
    currentHeight = currentHeight+1;
  }
}

TEST_CASE( "ZigZag" ) {
    node *root = make_node('A',
            make_node('B',
                make_node('G'),
                make_node('F')
                ),
            make_node('C',
                make_node('E'),
                make_node('D')
                )
            );
    stringstream ss;
    zigzag(root, ss);
    REQUIRE(ss.str() == "A C B G F E D ");
}
