/* Given a tree, e.g.
   A
   B       E
   C       DF      G
   print all the paths from root to leaves respecting horizontal offset of each in in-order traversal, e.g.

   _A
   B
   _D

   __A
   _B
   C

   A
   _E
   F
   .. and so on
   */
#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>

#include "../trees.h"

using namespace std;

void print_path(const vector<node*> &path, map<const node*, int> &offsets) { // [A, C, F] {A: 0 , C: 1, F:0}
    int min_offset = numeric_limits<int>::max();	// 99999
    for (auto it = path.begin(); it != path.end(); ++it) {
        const node *current = *it;
        min_offset = min(offsets[current], min_offset); // 0
    }
    for (auto it = path.begin(); it != path.end(); ++it) {
        node *current = *it;
        int currentOffset = offsets[current] - min_offset; // 0
        for(int i = 0; i < currentOffset; ++i) {
            cout << "_";
        }
        cout << current->value << "\n";
    }
    cout << "\n";
}

void iteratePaths(node *root, vector<node *> &path, map<const node*, int> offsets) { // a b d
    if(!root){
        print_path(path, offsets); 
        return;
    }
    path.push_back(root);
    iteratePaths(root->left, path, offsets);
    iteratePaths(root->right, path, offsets);
    path.pop_back();
}

void getOffsets(node *root, map<const node*, int> *offsets, int offset = 0) {
    if (!root) return;
    (*offsets)[root] = offset;
    getOffsets(root->left, offsets, offset-1);
    getOffsets(root->right, offsets, offset+1);
}


int main(int argc, const char**) {
    node *root = 
        make_node('A', 
                make_node('B', 
                    make_node('C'), make_node('D')
                    ),
                make_node('E',
                    make_node('F'), make_node('G')
                    )
                );
    /*
       A
       B       E
       C       DF      G
       */

    map<const node*, int> offsets;
    vector<node*> path;

    getOffsets(root, &offsets);
    iteratePaths(root, path, offsets);
    return 0;
}


