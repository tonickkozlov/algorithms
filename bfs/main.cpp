// Given a set of activities defined as {{S0, F0}, ..., {Sn, Fn}}
// find a subset of compatible activities with maximal size

#include <vector>
#include <string>

#include "./bfs.h"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

TEST_CASE( "BFS" ) {
    string s = "hello";
    map<char, edge_list> edges = {
        {'a', {'b', 'd'}},
        {'b', {'a', 'c', 'd', 'e'}},
        {'c', {'b', 'e'}},
        {'d', {'a', 'b', 'e'}},
        {'e', {'b', 'c', 'd', 'f'}},
        {'f', {'e'}}
    };

    map<char, int> expected = {
        {'a', 0},
        {'b', 1},
        {'d', 1},
        {'c', 2},
        {'e', 2},
        {'f', 3}
    };
    map<char, char> parents;
    REQUIRE(BFS(edges, 'a', &parents) == expected);
    // get shortest path between 'a' and 'f'
    string shortestPath;
    char current = 'f';
    while (true) {
        shortestPath += current;
        auto it = parents.find(current);
        if (it == parents.end()) {
            shortestPath = "not found";
            break;
        }
        if (it->second == 'a') {
            shortestPath += it->second;
            break;
        }
        current = it->second;
    }
    REQUIRE(shortestPath == "feba");
}
